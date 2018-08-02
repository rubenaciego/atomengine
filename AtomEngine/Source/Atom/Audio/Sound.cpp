#include <gorilla/ga.h>
#include <gorilla/gau.h>
#include <Atom/Audio/AudioManager.hpp>
#include <Atom/Utils/StringUtils.hpp>
#include <Atom/Debug/Debug.hpp>
#include <Atom/Audio/Sound.hpp>

namespace atom
{
	void DestroyOnFinish(ga_Handle* in_handle, void* in_context);

	Sound::Sound(const std::string& name, const std::string& path)
	{
		m_Name = name;
		m_Sound = gau_load_sound_file(path.c_str(), GetExtension(path).c_str());
		m_Loop = nullptr;
		m_Playing = false;
	}
	
	Sound::~Sound()
	{
		Stop();
		ga_sound_release(m_Sound);
	}
	
	void Sound::Play()
	{
		Stop();
	
		m_Handle = gau_create_handle_sound(AudioManager::m_Mixer, m_Sound,
			&DestroyOnFinish, nullptr, nullptr);
		ga_handle_play(m_Handle);
		m_Handle->sound = (void*)this;
		
		m_Playing = true;

		Debug::Log("Playing sound " + m_Name + "\n");
	}
	
	void Sound::Loop()
	{
		Stop();
		
		m_Handle = gau_create_handle_sound(AudioManager::m_Mixer, m_Sound,
			&DestroyOnFinish, nullptr, &m_Loop);
		ga_handle_play(m_Handle);
		m_Handle->sound = (void*)this;
	
		m_Playing = true;

		Debug::Log("Playing sound " + m_Name + " in loop\n");
	}
	
	void Sound::Resume()
	{
		if (m_Playing)
			return;

		ga_handle_play(m_Handle);
		m_Playing = true;

		Debug::Log("Resumed sound " + m_Name + "\n");
	}
	
	void Sound::Pause()
	{
		if (!m_Playing)
			return;
	
		ga_handle_stop(m_Handle);
		m_Playing = false;

		Debug::Log("Paused sound " + m_Name + "\n");
	}
	
	void Sound::Stop()
	{
		if (!m_Playing)
			return;
	
		ga_handle_stop(m_Handle);
		m_Playing = false;
		ga_handle_destroy(m_Handle);

		Debug::Log("Stopped sound " + m_Name + "\n");
	}
	
	void Sound::SetGain(float gain)
	{
		if (!m_Playing)
		{
			Debug::Error("Cannot set the audio gain of" + m_Name + "if it's not playing!\n");
			return;
		}
		
		m_Gain = gain;
		ga_handle_setParamf(m_Handle, GA_HANDLE_PARAM_GAIN, gain);
	}
	
	float Sound::GetGain() const
	{
		return m_Gain;
	}
	
	bool Sound::IsPlaying() const
	{
		return m_Playing;
	}
	
	void DestroyOnFinish(ga_Handle* in_handle, void* in_context)
	{
		((Sound*)in_handle->sound)->m_Playing = false;
		ga_handle_destroy(in_handle);
	}
}
