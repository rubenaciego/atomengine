#pragma once

#include <Atom/Time/Timer.hpp>

namespace atom
{
	class Time
	{
	public:
		static float timeScale;

		inline static float DeltaTime() { return m_DeltaTime * timeScale; }

	private:
		Time() {}

		static float m_DeltaTime;
		static Timer m_Timer;

		friend class Engine;
	};
}
