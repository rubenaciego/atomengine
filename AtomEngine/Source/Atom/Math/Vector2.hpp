#pragma once

namespace Atom
{
	struct Vector2
	{
	public:
		float x;
		float y;
	
		Vector2();
		Vector2(const float& x, const float& y);
	
		Vector2& Add(const Vector2 &other);
		Vector2& Subtract(const Vector2 &other);
		Vector2& Multiply(const float &num);
		Vector2& Divide(const float &num);
	
		Vector2& operator+=(const Vector2 &other);
		Vector2& operator-=(const Vector2 &other);
		Vector2& operator*=(const float &num);
		Vector2& operator/=(const float &num);
	
		bool operator==(const Vector2 &other);
		bool operator!=(const Vector2 &other);
	
		friend Vector2 operator+(Vector2 left, const Vector2 &right);
		friend Vector2 operator-(Vector2 left, const Vector2 &right);
		friend Vector2 operator*(Vector2 vector, const float &num);
		friend Vector2 operator/(Vector2 vector, const float &num);
	};
}
