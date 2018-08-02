#include <Atom/Graphics/Renderer2D.hpp>
#include <Atom/Graphics/Renderables/Renderable2D.hpp>
#include <Atom/Debug/Debug.hpp>
#include <Atom/Graphics/Shader.hpp>
#include <Atom/Graphics/Layers/Layer.hpp>

namespace atom
{
	Layer::Layer(Renderer2D* renderer, Shader* shader, const Matrix4 &projectionMatrix)
		: m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix)
	{
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("pr_matrix", m_ProjectionMatrix);
		m_Shader->Unbind();

		Debug::Log("Layer created\n");
	}

	Layer::~Layer()
	{
		delete m_Shader;
		delete m_Renderer;

		for (unsigned int i = 0; i < m_Renderables.size(); i++)
			delete m_Renderables[i];

		Debug::Log("Layer destroyed\n");
	}

	void Layer::Add(Renderable2D* renderable)
	{
		m_Renderables.push_back(renderable);

		Debug::Log("Renderable2D added to the layer\n");
	}

	void Layer::Render()
	{
		m_Shader->Bind();
		m_Renderer->Begin();

		for (const Renderable2D* i : m_Renderables)
			i->Submit(m_Renderer);

		m_Renderer->End();
		m_Renderer->Flush();
	}
}
