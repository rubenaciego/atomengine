#pragma once

#include <vector>

struct gau_Manager;
struct ga_Mixer;

namespace atom
{
	class Sound;
	
	class AudioManager
	{
	private:
		AudioManager() {}
	
		static gau_Manager* m_Manager;
		static ga_Mixer* m_Mixer;
		static std::vector<Sound*> m_Sounds;
	
	public:
		static void Init();
		static void Add(Sound* sound);
		static Sound* Get(const std::string& name);
		static void Clean();
		static void Clear();
		static void Update();
	
		friend class Sound;
	};
}
