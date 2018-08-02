#pragma once

#include <vector>
#include <Atom/Math/Matrix4.hpp>

namespace atom
{
	class Renderer2D;
	class Renderable2D;
	class Shader;

	class Layer
	{
	protected:
		Renderer2D* m_Renderer;
		Shader* m_Shader;
		Shader* m_TextShader;
		Matrix4 m_ProjectionMatrix;
		std::vector<Renderable2D*> m_Renderables;

		Layer(Renderer2D* renderer, Shader* shader, const Matrix4 &projectionMatrix);

	public:
		virtual ~Layer();
		virtual void Add(Renderable2D* renderable);
		virtual void Render();
	};
}
