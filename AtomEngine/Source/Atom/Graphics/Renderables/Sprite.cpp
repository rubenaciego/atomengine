#include <Atom/Graphics/Renderables/Sprite.hpp>

namespace Atom
{
	Sprite::Sprite(float x, float y, float width, float height, const Color &color)
		: Renderable2D(Vector3(x, y, 0), Vector2(width, height), color)
	{
	}

	Sprite::Sprite(float x, float y, float width, float height, Texture *texture)
		: Renderable2D(Vector3(x, y, 0), Vector2(width, height), Color(0xffffffff))
	{
		m_Texture = texture;
	}
}
