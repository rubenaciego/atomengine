#include <gorilla/ga.h>
#include <gorilla/gau.h>
#include <Atom/Debug/Debug.hpp>
#include <Atom/Audio/Sound.hpp>
#include <Atom/Audio/AudioManager.hpp>

namespace atom
{
	gau_Manager* AudioManager::m_Manager = nullptr;
	ga_Mixer* AudioManager::m_Mixer = nullptr;
	std::vector<Sound*> AudioManager::m_Sounds;

	void AudioManager::Init()
	{
		gc_initialize(0);
		m_Manager = gau_manager_create();
		m_Mixer = gau_manager_mixer(m_Manager);

		Debug::Log("Audio Manager initialized\n");
	}

	void AudioManager::Add(Sound* sound)
	{
		m_Sounds.push_back(sound);

		Debug::Log("Sound " + sound->m_Name + " added\n");
	}

	Sound* AudioManager::Get(const std::string& name)
	{
		for (Sound* sound : m_Sounds)
		{
			if (sound->m_Name == name)
				return sound;
		}

		return nullptr;
	}

	void AudioManager::Clean()
	{
		for (Sound* i : m_Sounds)
			delete i;

		gau_manager_destroy(m_Manager);
		gc_shutdown();

		Debug::Log("Audio Manager cleaned\n");
	}

	void AudioManager::Clear()
	{
		for (Sound* i : m_Sounds)
			delete i;

		Debug::Log("All sounds deleted\n");
	}

	void AudioManager::Update()
	{
		gau_manager_update(m_Manager);
	}
}
