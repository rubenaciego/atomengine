#pragma once

#include <cmath>
#include <Atom/Math/Vector2.hpp>
#include <Atom/Math/Vector3.hpp>
#include <Atom/Math/Vector4.hpp>
#include <Atom/Math/Matrix4.hpp>
#include <Atom/Math/Random.hpp>

namespace Atom
{
	namespace Math
	{
		extern const float E;
		extern const float LOG2E;
		extern const float LOG10E;
		extern const float LN2;
		extern const float LN10;
		extern const float PI;
		extern const float PI_2;
		extern const float PI_4;
		extern const float SQRT2;
		extern const float SQRT1_2;

		float ToRadians(float degrees);
		float ToDegrees(float radians);
		float Tan(float val);
		float Sin(float val);
		float Cos(float val);
		float ArcSin(float val);
		float ArcCos(float val);
		float ArcTan(float val);
		float Sqrt(float val);
		float Power(float val, float power);
		float Abs(float val);
	}
}
