#pragma once

#include <string>

namespace ftgl
{
	struct texture_atlas_t;
	struct texture_font_t;
}

namespace atom
{
	struct Font
	{
	private:
		ftgl::texture_atlas_t* m_Atlas;
		ftgl::texture_font_t* m_Font;
		std::string m_Name;
		unsigned int m_Size;

	public:
		Font(const std::string &fontpath, const std::string &name, unsigned int size);

		friend class Label;
		friend class Renderer2D;
		friend class FontManager;
	};
}
