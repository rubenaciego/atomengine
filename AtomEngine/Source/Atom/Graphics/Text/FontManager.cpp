#include <Atom/Debug/Debug.hpp>
#include <Atom/Graphics/Text/Font.hpp>
#include <Atom/Graphics/Text/FontManager.hpp>

namespace Atom
{
	extern unsigned char arialData[];
	extern unsigned int arialDataLenght;

	namespace FontManager
	{
		std::vector<Font*> fonts;

		void Init()
		{
			Add(new Font(arialData, arialDataLenght, "ArialDefault", 50));

			Debug::Log("[Atom]: Font Manager initialized\n");
		}

		void Add(Font* font)
		{
			fonts.push_back(font);

			Debug::Log("[Atom]: Font " + font->m_Name + " added\n");
		}

		Font* FontManager::Get(const std::string& name)
		{
			for (Font* font : fonts)
			{
				if (font->m_Name == name)
					return font;
			}

			Debug::Warning("[Atom]: Font \"" + name + "\" not found, using default font instead\n");

			return fonts[0];
		}

		Font* FontManager::Get(const std::string& name, unsigned int size)
		{
			for (Font* font : fonts)
			{
				if (font->m_Size == size && font->m_Name == name)
					return font;
			}

			Debug::Warning("[Atom]: Font: " + name + " not found, using default font instead\n");

			return fonts[0];
		}

		void FontManager::Clean()
		{
			for (unsigned int i = 0; i < fonts.size(); i++)
				delete fonts[i];

			Debug::Log("[Atom]: Font Manager cleaned\n");
		}
	}
}
