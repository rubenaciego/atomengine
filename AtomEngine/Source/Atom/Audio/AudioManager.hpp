#pragma once

#include <string>

namespace Atom
{
	class Sound;
	
	namespace AudioManager
	{
		void Init();
		void Add(Sound* sound);
		Sound* Get(const std::string& name);
		void Clean();
		void Clear();
		void Update();
	};
}
