#pragma once

#include <math.h>
#include <Atom/Math/Vector2.hpp>
#include <Atom/Math/Vector3.hpp>
#include <Atom/Math/Vector4.hpp>
#include <Atom/Math/Matrix4.hpp>
#include <Atom/Math/Random.hpp>

namespace atom
{
	class Math
	{
	public:
		static const float E;
		static const float LOG2E;
		static const float LOG10E;
		static const float LN2;
		static const float LN10;
		static const float PI;
		static const float PI_2;
		static const float PI_4;
		static const float SQRT2;
		static const float SQRT1_2;

		static inline float ToRadians(float degrees) { return degrees * PI / 180.0f; }
		static inline float ToDegrees(float radians) { return radians * 180.0f / PI; }
		static inline float Tan(float val) { return tan(val); }
		static inline float Sin(float val) { return sin(val); }
		static inline float Cos(float val) { return cos(val); }
		static inline float ArcSin(float val) { return asin(val); }
		static inline float ArcCos(float val) { return acos(val); }
		static inline float ArcTan(float val) { return atan(val); }
		static inline float Sqrt(float val) { return sqrt(val); }
		static inline float Power(float val, float power) { return pow(val, power); }
		static inline float Abs(float val) { return fabsf(val); }
	
	private:
		Math() {}
	};
}
