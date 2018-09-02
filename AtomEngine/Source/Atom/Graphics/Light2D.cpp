#include <Atom/Graphics/Light2D.hpp>
#include <Atom/Graphics/Shaders/Shader.hpp>
#include <Atom/Graphics/OpenGL.hpp>
#include <Atom/Graphics/Camera.hpp>
#include <Atom/Graphics/Renderer2D.hpp>
#include <Atom/Graphics/Texture.hpp>
#include <Atom/Engine.hpp>
#include <Atom/Graphics/Window.hpp>

namespace Atom
{
	Light2D::Light2D(int bufferSize, Vector2 pos, Color color) :
		m_OccludersFBO(bufferSize , bufferSize),
		m_ShadowMapFBO(bufferSize, 1),
		m_RenderSprite(pos.x, pos.y, 32.0f / (float)Engine::m_Window->GetWidth() * bufferSize, 18.0f / (float)Engine::m_Window->GetHeight() * bufferSize, new Texture(bufferSize, 1, m_ShadowMapFBO.GetTexID())),
		m_OccludersSprite(16.0f / (float)Engine::m_Window->GetWidth() * bufferSize - 16.0f, 9.0f / (float)Engine::m_Window->GetHeight() * bufferSize - 9.0f, bufferSize / 32.0f, bufferSize / 32.0f, new Texture(bufferSize, bufferSize, m_OccludersFBO.GetTexID()))
	{
		m_BufferSize = bufferSize;
		m_RenderSprite.SetColor(color);
		m_CamPos = Vector2((Engine::m_Window->GetWidth() - m_BufferSize) / 64.0f + m_RenderSprite.GetPosition().x, (Engine::m_Window->GetHeight() - m_BufferSize) / 64.0f + m_RenderSprite.GetPosition().y);
	}

	void Light2D::Begin(Renderer2D* renderer, Shader* shader, Shader* shadowShader)
	{
		shadowShader->Bind();
		shadowShader->SetUniform2f("resolution", Vector2(m_BufferSize, m_BufferSize));

		m_Camera.position = m_CamPos;

		m_OccludersFBO.Bind();
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		shader->Bind();
		renderer->Begin(&m_Camera);
	}

	void Light2D::End(Renderer2D* renderer, Shader* shader, Shader* shadowShader)
	{
		renderer->End();
		renderer->Flush();
		m_OccludersFBO.Unbind();

		m_ShadowMapFBO.Bind();
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		shadowShader->Bind();
		renderer->Begin(&m_Camera);
		
		m_Camera.position = Vector2(0.0f, 0.0f);
		m_OccludersSprite.Submit(renderer);

		renderer->End();
		renderer->Flush();
		m_ShadowMapFBO.Unbind();

		renderer->Begin(&m_Camera);
		shadowShader->SetUniform1i("shadow", 1);

		m_RenderSprite.Submit(renderer);

		renderer->End();
		renderer->Flush();
		shadowShader->SetUniform1i("shadow", 0);
	}
}
