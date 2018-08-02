#pragma once

namespace atom
{
	class Random
	{
	public:
		static void Init();
		static float NextFloat();
		static int NextInt(int minimum, int maximum);

	private:
		Random() {}
	};
}
