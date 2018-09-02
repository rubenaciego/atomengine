#include <cstdlib>
#include <ctime>
#include <Atom/Math/Random.hpp>

namespace Atom
{
	namespace Random
	{
		void Init()
		{
			srand((unsigned int)time(nullptr));
		}

		float NextFloat()
		{
			return (float)rand() / RAND_MAX;
		}

		int NextInt(int minimum, int maximum)
		{
			return rand() % (maximum - minimum) + minimum;
		}
	}
}
