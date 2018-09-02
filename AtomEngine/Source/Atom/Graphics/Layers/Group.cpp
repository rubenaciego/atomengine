#include <Atom/Graphics/Renderer2D.hpp>
#include <Atom/Graphics/Layers/Group.hpp>

namespace Atom
{
	Group::Group(const Matrix4 &transform) : m_TransformationMatrix(transform)
	{
	}

	Group::~Group()
	{
		for (unsigned int i = 0; i < m_Renderables.size(); i++)
			delete m_Renderables[i];
	}

	void Group::Add(Renderable2D* renderable)
	{
		m_Renderables.push_back(renderable);
	}

	void Group::Submit(Renderer2D* renderer) const
	{
		renderer->PushMatrix(m_TransformationMatrix);

		for (const Renderable2D* i : m_Renderables)
			i->Submit(renderer);

		renderer->PopMatrix();
	}
}
