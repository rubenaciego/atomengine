#include <Atom/Math/Math.hpp>

namespace Atom
{
	namespace Math
	{
		const float E = 2.71828182845904523536f;
		const float LOG2E = 1.44269504088896340736f;
		const float LOG10E = 0.434294481903251827651f;
		const float LN2 = 0.693147180559945309417f;
		const float LN10 = 2.30258509299404568402f;
		const float PI = 3.14159265358979323846f;
		const float PI_2 = 1.57079632679489661923f;
		const float PI_4 = 0.785398163397448309616f;
		const float SQRT2 = 1.41421356237309504880f;
		const float SQRT1_2 = 0.707106781186547524401f;

		float ToRadians(float degrees) { return degrees * PI / 180.0f; }
		float ToDegrees(float radians) { return radians * 180.0f / PI; }
		float Tan(float val) { return tan(val); }
		float Sin(float val) { return sin(val); }
		float Cos(float val) { return cos(val); }
		float ArcSin(float val) { return asin(val); }
		float ArcCos(float val) { return acos(val); }
		float ArcTan(float val) { return atan(val); }
		float Sqrt(float val) { return sqrt(val); }
		float Power(float val, float power) { return pow(val, power); }
		float Abs(float val) { return fabsf(val); }
	}
}
