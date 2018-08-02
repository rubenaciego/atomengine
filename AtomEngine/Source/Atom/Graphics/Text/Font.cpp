#include <freetype-gl.h>
#include <Atom/Debug/Debug.hpp>
#include <Atom/Graphics/Text/Font.hpp>

namespace atom
{
	Font::Font(const std::string &fontpath, const std::string& name, unsigned int size)
	{
		using namespace ftgl;

		m_Atlas = texture_atlas_new(512, 512, 2);
		m_Font = texture_font_new_from_file(m_Atlas, (float)size, fontpath.c_str());
		m_Name = fontpath;
		m_Size = size;
		m_Name = name;

		Debug::Log("Font " + name + " created\n");
	}
}
