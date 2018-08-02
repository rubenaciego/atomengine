#pragma once

#include <vector>

namespace atom
{
	struct Font;

	class FontManager
	{
	private:
		FontManager() {}
		static std::vector<Font*> m_Fonts;

	public:
		static void Init();
		static void Add(Font* font);
		static Font* Get(const std::string& name);
		static Font* Get(const std::string& name, unsigned int size);
		static void Clean();
	};
}

