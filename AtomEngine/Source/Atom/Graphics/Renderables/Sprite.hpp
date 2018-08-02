#pragma once

#include <Atom/Graphics/Renderables/Renderable2D.hpp>

namespace atom
{
	class Sprite : public Renderable2D
	{
	public:
		Sprite(float x, float y, float width, float height, const Color &color);
		Sprite(float x, float y, float width, float height, Texture *texture);
	};
}
