#pragma once

#include <Atom/Graphics/Buffers/FrameBuffer.hpp>
#include <Atom/Graphics/Renderables/Sprite.hpp>
#include <Atom/Graphics/Layers/Layer.hpp>
#include <Atom/Graphics/Camera.hpp>

namespace Atom
{
	class Light2D
	{
	private:
		int m_BufferSize;
		FrameBuffer m_OccludersFBO;
		FrameBuffer m_ShadowMapFBO;
		Sprite m_RenderSprite;
		Sprite m_OccludersSprite;
		Vector2 m_CamPos;
		Camera m_Camera;

	public:
		Light2D(int bufferSize, Vector2 pos, Color color);
		void Begin(Renderer2D* renderer, Shader* shader, Shader* shadowShader);
		void End(Renderer2D* renderer, Shader* shader, Shader* shadowShader);

		friend class Layer;
	};
}
