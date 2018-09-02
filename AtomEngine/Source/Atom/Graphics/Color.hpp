#pragma once

namespace Atom
{
	struct Color
	{
		union
		{
			unsigned int color;
	
			struct
			{
				unsigned char red;
				unsigned char green;
				unsigned char blue;
				unsigned char alpha;
			};
		};
	
		Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255);
		Color(unsigned int color);
	};
}
