#pragma once

#include <vector>
#include <Atom/Graphics/Renderables/Renderable2D.hpp>

namespace Atom
{
	class Renderer2D;

	class Group : public Renderable2D
	{
	private:
		std::vector<Renderable2D*> m_Renderables;
		Matrix4 m_TransformationMatrix;

	public:
		Group(const Matrix4 &transform);
		~Group();

		void Add(Renderable2D* renderable);
		void Submit(Renderer2D* renderer) const override;
	};
}
