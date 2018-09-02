#include <Atom/Graphics/Renderer2D.hpp>
#include <Atom/Graphics/Renderables/Renderable2D.hpp>
#include <Atom/Debug/Debug.hpp>
#include <Atom/Graphics/Shaders/Shader.hpp>
#include <Atom/Graphics/Layers/Layer.hpp>
#include <Atom/Utils/FileUtils.hpp>
#include <Atom/Graphics/Light2D.hpp>

namespace Atom
{
	Layer::Layer(Renderer2D* renderer, Shader* shader)
		: m_Renderer(renderer), m_ProjectionMatrix(Matrix4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
	{
		if (shader == nullptr)
			m_Shader = Shader::StandardShader2D();
		else
			m_Shader = shader;

		m_ShadowShader = Shader::ShadowShader2D();

		m_Shader->Bind();
		m_Shader->SetUniformMat4f("pr_matrix", m_ProjectionMatrix);

		int textures[16] = {
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
		};

		m_Shader->SetUniform1iv("u_Textures", 16, textures);

		m_ShadowShader->Bind();
		m_ShadowShader->SetUniformMat4f("pr_matrix", m_ProjectionMatrix);

		Debug::Log("[Atom]: Layer created\n");
	}

	Layer::~Layer()
	{
		delete m_Shader;
		delete m_ShadowShader;
		delete m_Renderer;

		for (unsigned int i = 0; i < m_Renderables.size(); i++)
			delete m_Renderables[i];

		Debug::Log("[Atom]: Layer destroyed\n");
	}

	void Layer::Add(Renderable2D* renderable)
	{
		m_Renderables.push_back(renderable);
	}

	void Layer::Add(Light2D* light)
	{
		m_Lights.push_back(light);
	}

	void Layer::Render(Camera* cam)
	{
		for (Light2D* i : m_Lights)
		{
			i->Begin(m_Renderer, m_Shader, m_ShadowShader);

			for (const Renderable2D* renderable : m_Renderables)
				renderable->Submit(m_Renderer);

			i->End(m_Renderer, m_Shader, m_ShadowShader);
		}

		m_Renderer->Begin(cam);
		m_Shader->Bind();

		for (const Renderable2D* i : m_Renderables)
			i->Submit(m_Renderer);

		m_Renderer->End();
		m_Renderer->Flush();
	}
}
