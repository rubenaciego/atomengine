#pragma once

#include <Atom/Math/Math.hpp>

namespace Atom
{
	struct Camera
	{
	public:
		Vector2 position;

		Camera(): position(0.0f, 0.0f) {}
	};
}
