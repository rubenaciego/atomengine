#include <freetype-gl.h>
#include <Atom/Debug/Debug.hpp>
#include <Atom/Graphics/Text/Font.hpp>

/* Add support for loading from memory
 * and be able to inline the default font
 */

namespace Atom
{
	Font::Font(const std::string &fontpath, const std::string& name, unsigned int size)
	{
		using namespace ftgl;

		m_Atlas = texture_atlas_new(512, 512, 2);
		m_Font = texture_font_new_from_file(m_Atlas, (float)size, fontpath.c_str());
		m_Size = size;
		m_Name = name;

		Debug::Log("[Atom]: Font " + name + " created\n");
	}

	Font::Font(const void* data, int dataSize, const std::string& name, unsigned int size)
	{
		using namespace ftgl;

		m_Atlas = texture_atlas_new(512, 512, 2);
		m_Font = texture_font_new_from_memory(m_Atlas, (float)size, data, dataSize);
		m_Size = size;
		m_Name = name;

		Debug::Log("[Atom]: Font " + name + " created\n");
	}
}
