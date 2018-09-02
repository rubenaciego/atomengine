#include <vector>
#include <gorilla/ga.h>
#include <gorilla/gau.h>
#include <Atom/Debug/Debug.hpp>
#include <Atom/Audio/Sound.hpp>
#include <Atom/Audio/AudioManager.hpp>

namespace Atom
{
	namespace AudioManager
	{
		gau_Manager* manager = nullptr;
		ga_Mixer* mixer = nullptr;
		std::vector<Sound*> sounds;

		void Init()
		{
			gc_initialize(0);
			manager = gau_manager_create();
			mixer = gau_manager_mixer(manager);

			Debug::Log("[Atom]: Audio Manager initialized\n");
		}

		void Add(Sound* sound)
		{
			sounds.push_back(sound);

			Debug::Log("[Atom]: Sound " + sound->m_Name + " added\n");
		}

		Sound* Get(const std::string& name)
		{
			for (Sound* sound : sounds)
			{
				if (sound->m_Name == name)
					return sound;
			}

			return nullptr;
		}

		void Clean()
		{
			for (Sound* i : sounds)
				delete i;

			gau_manager_destroy(manager);
			gc_shutdown();

			Debug::Log("[Atom]: Audio Manager cleaned\n");
		}

		void Clear()
		{
			for (Sound* i : sounds)
				delete i;

			Debug::Log("[Atom]: All sounds deleted\n");
		}

		void Update()
		{
			gau_manager_update(manager);
		}
	}
}
