#pragma once

#include <vector>
#include <Atom/Math/Matrix4.hpp>
#include <Atom/Graphics/Buffers/FrameBuffer.hpp>

namespace Atom
{
	class Renderer2D;
	class Renderable2D;
	class Shader;
	class Light2D;
	struct Camera;

	class Layer
	{
	protected:
		Renderer2D* m_Renderer;
		Shader* m_Shader;
		Shader* m_ShadowShader;
		Matrix4 m_ProjectionMatrix;
		std::vector<Light2D*> m_Lights;
		std::vector<Renderable2D*> m_Renderables;

	public:
		Layer(Renderer2D* renderer, Shader* shader);
		virtual ~Layer();
		virtual void Add(Renderable2D* renderable);
		virtual void Add(Light2D* light);
		virtual void Render(Camera* cam);
	};
}
