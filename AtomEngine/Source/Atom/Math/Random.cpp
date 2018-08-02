#include <cstdlib>
#include <ctime>
#include <Atom/Math/Random.hpp>

namespace atom
{
	void Random::Init()
	{
		srand((unsigned int)time(nullptr));
	}

	float Random::NextFloat()
	{
		return (float)rand() / RAND_MAX;
	}

	int Random::NextInt(int minimum, int maximum)
	{
		return rand() % (maximum - minimum) + minimum;
	}
}
