#pragma once

#include <chrono>

namespace Atom
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
