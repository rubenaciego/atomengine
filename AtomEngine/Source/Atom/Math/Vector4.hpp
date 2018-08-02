#pragma once

namespace atom
{
	struct Vector4
	{
	public:
		float x;
		float y;
		float z;
		float w;
	
		Vector4();
		Vector4(const float& x, const float& y, const float& z, const float &w);
	
		Vector4& Add(const Vector4 &other);
		Vector4& Subtract(const Vector4 &other);
		Vector4& Multiply(const float &num);
		Vector4& Divide(const float &num);
	
		Vector4& operator+=(const Vector4 &other);
		Vector4& operator-=(const Vector4 &other);
		Vector4& operator*=(const float &num);
		Vector4& operator/=(const float &num);
	
		bool operator==(const Vector4 &other);
		bool operator!=(const Vector4 &other);
	
		friend Vector4 operator+(Vector4 left, const Vector4 &right);
		friend Vector4 operator-(Vector4 left, const Vector4 &right);
		friend Vector4 operator*(Vector4 vector, const float &num);
		friend Vector4 operator/(Vector4 vector, const float &num);
	};
}
