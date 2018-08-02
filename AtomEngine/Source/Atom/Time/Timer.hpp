#pragma once

#include <chrono>

namespace atom
{
	class Timer
	{
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;

	public:
		Timer();

		void Reset();
		float Elapsed();
		float Tick();
	};
}
