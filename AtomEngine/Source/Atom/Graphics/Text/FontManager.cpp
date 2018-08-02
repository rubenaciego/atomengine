#include <Atom/Debug/Debug.hpp>
#include <Atom/Graphics/Text/Font.hpp>
#include <Atom/Graphics/Text/FontManager.hpp>

namespace atom
{
	std::vector<Font*> FontManager::m_Fonts;

	void FontManager::Init()
	{
		Add(new Font("Fonts/Arial.ttf", "ArialDefault", 50));

		Debug::Log("Font Manager initialized\n");
	}

	void FontManager::Add(Font* font)
	{
		m_Fonts.push_back(font);

		Debug::Log("Font " + font->m_Name + " added\n");
	}

	Font* FontManager::Get(const std::string& name)
	{
		for (Font* font : m_Fonts)
		{
			if (font->m_Name == name)
				return font;
		}

		Debug::Warning("Font \"" + name + "\" not found, using default font instead\n");

		return m_Fonts[0];
	}

	Font* FontManager::Get(const std::string& name, unsigned int size)
	{
		for (Font* font : m_Fonts)
		{
			if (font->m_Size == size && font->m_Name == name)
				return font;
		}

		Debug::Warning("Font: " + name + " not found, using default font instead\n");
		
		return m_Fonts[0];
	}

	void FontManager::Clean()
	{
		for (unsigned int i = 0; i < m_Fonts.size(); i++)
			delete m_Fonts[i];

		Debug::Log("Font Manager cleaned\n");
	}
}
