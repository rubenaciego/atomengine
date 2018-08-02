#include <Atom/Graphics/Color.hpp>

namespace atom
{
	Color::Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
	{
		this->red = red;
		this->green = green;
		this->blue = blue;
		this->alpha = alpha;
	}

	Color::Color(unsigned int color)
	{
		this->color = color;
	}
}
