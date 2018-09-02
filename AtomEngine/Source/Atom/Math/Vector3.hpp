#pragma once

namespace Atom
{
	struct Vector3
	{
	public:
		float x;
		float y;
		float z;
	
		Vector3();
		Vector3(const float& x, const float& y, const float&z);
	
		Vector3& Add(const Vector3 &other);
		Vector3& Subtract(const Vector3 &other);
		Vector3& Multiply(const float &num);
		Vector3& Divide(const float &num);
	
		Vector3& operator+=(const Vector3 &other);
		Vector3& operator-=(const Vector3 &other);
		Vector3& operator*=(const float &num);
		Vector3& operator/=(const float &num);
	
		bool operator==(const Vector3 &other);
		bool operator!=(const Vector3 &other);
	
		friend Vector3 operator+(Vector3 left, const Vector3 &right);
		friend Vector3 operator-(Vector3 left, const Vector3 &right);
		friend Vector3 operator*(Vector3 vector, const float &num);
		friend Vector3 operator/(Vector3 vector, const float &num);	
	};
}
