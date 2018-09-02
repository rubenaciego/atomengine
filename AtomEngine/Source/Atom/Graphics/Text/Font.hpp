#pragma once

#include <string>
#include <Atom/Graphics/Text/FontManager.hpp>

namespace ftgl
{
	struct texture_atlas_t;
	struct texture_font_t;
}

namespace Atom
{
	struct Font
	{
	private:
		ftgl::texture_atlas_t* m_Atlas;
		ftgl::texture_font_t* m_Font;
		std::string m_Name;
		unsigned int m_Size;

	public:
		Font(const std::string &fontpath, const std::string& name, unsigned int size);
		Font(const void* data, int dataSize, const std::string& name, unsigned int size);

		friend class Label;
		friend class Renderer2D;
		friend Font* FontManager::Get(const std::string& name);
		friend Font* FontManager::Get(const std::string& name, unsigned int size);
		friend void FontManager::Add(Font* font);
	};
}
