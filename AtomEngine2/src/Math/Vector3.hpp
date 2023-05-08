#pragma once

namespace atom
{
	class Vector2;
	class Quaternion;

	class Vector3
	{
	public:
		static const Vector3 UP;
		static const Vector3 DOWN;
		static const Vector3 LEFT;
		static const Vector3 RIGHT;
		static const Vector3 FORWARD;
		static const Vector3 BACK;
		static const Vector3 ONE;
		static const Vector3 ZERO;

		float x, y, z;

		Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);

		float Length() const;
		float LengthSq() const;
		float Dot(const Vector3& v) const;
		float Max() const;

		Vector3 Cross(const Vector3& v) const;
		Vector3 Rotate(const Vector3& axis, float angle) const;
		Vector3 Rotate(const Quaternion& q) const;
		Vector3 Lerp(const Vector3& dest, float factor) const;

		Vector3& Normalize();
		Vector3 Normalized() const;

		Vector2 GetXY() const;
		Vector2 GetYZ() const;
		Vector2 GetZX() const;
		Vector2 GetYX() const;
		Vector2 GetZY() const;
		Vector2 GetXZ() const;

		Vector3& operator+=(const Vector3& r);
		Vector3& operator-=(const Vector3& r);
		Vector3& operator*=(float f);
		Vector3& operator/=(float f);
		Vector3& operator*=(const Vector3& v);
		Vector3& operator/=(const Vector3& v);

		Vector3 operator+(const Vector3& r) const;
		Vector3 operator-(const Vector3& r) const;
		Vector3 operator*(float f) const;
		Vector3 operator/(float f) const;
		Vector3 operator*(const Vector3& v) const;
		Vector3 operator/(const Vector3& v) const;

		bool operator==(const Vector3& r) const;
		bool operator!=(const Vector3& r) const;
	};
}
