#include <Atom/Time/Timer.hpp>

namespace atom
{
	Timer::Timer()
	{
		Reset();
	}

	void Timer::Reset()
	{
		m_Start = std::chrono::high_resolution_clock::now();
	}

	float Timer::Elapsed()
	{
		return std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(
			std::chrono::high_resolution_clock::now() - m_Start).count() / 1000.0f;
	}

	float Timer::Tick()
	{
		float elapsed = Elapsed();
		Reset();

		return elapsed;
	}
}
