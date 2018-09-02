#pragma once

#include <vector>

namespace Atom
{
	struct Font;

	namespace FontManager
	{
		void Init();
		void Add(Font* font);
		Font* Get(const std::string& name);
		Font* Get(const std::string& name, unsigned int size);
		void Clean();
	};
}

