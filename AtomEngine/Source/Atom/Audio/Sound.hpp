#pragma once

#include <string>
#include <Atom/Audio/AudioManager.hpp>

struct ga_Sound;
struct ga_Handle;
struct gau_SampleSourceLoop;

namespace Atom
{
	class Sound
	{
	private:
		std::string m_Name;
		ga_Sound* m_Sound;
		ga_Handle* m_Handle;
		gau_SampleSourceLoop* m_Loop;
		bool m_Playing;
		float m_Gain;
	
	public:
		Sound(const std::string& name, const std::string& path);
		~Sound();
	
		void Play();
		void Loop();
		void Resume();
		void Pause();
		void Stop();
		void SetGain(float gain);
	
		float GetGain() const;
		bool IsPlaying() const;
	
		friend void DestroyOnFinish(ga_Handle* in_handle, void* in_context);
		friend void AudioManager::Add(Sound* sound);
		friend Sound* AudioManager::Get(const std::string& name);
	};
}
