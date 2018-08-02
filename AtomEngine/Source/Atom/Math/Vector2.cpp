#include <Atom/Math/Vector2.hpp>

namespace atom
{
	Vector2::Vector2()
	{
		x = 0.0f;
		y = 0.0f;
	}
	
	Vector2::Vector2(const float& x, const float& y)
	{
		this->x = x;
		this->y = y;
	}
	
	Vector2& Vector2::Add(const Vector2 &other)
	{
		x += other.x;
		y += other.y;
	
		return *this;
	}
	
	Vector2& Vector2::Subtract(const Vector2 &other)
	{
		x -= other.x;
		y -= other.y;
	
		return *this;
	}
	
	Vector2& Vector2::Multiply(const float &num)
	{
		x *= num;
		y *= num;
	
		return *this;
	}
	
	Vector2& Vector2::Divide(const float &num)
	{
		x /= num;
		y /= num;
	
		return *this;
	}
	
	Vector2 operator+(Vector2 left, const Vector2 &right)
	{
		return left.Add(right);
	}
	
	Vector2 operator-(Vector2 left, const Vector2 &right)
	{
		return left.Subtract(right);
	}
	
	Vector2 operator*(Vector2 vector, const float &num)
	{
		return vector.Multiply(num);
	}
	
	Vector2 operator/(Vector2 vector, const float &num)
	{
		return vector.Divide(num);
	}
	
	Vector2& Vector2::operator+=(const Vector2 &other)
	{
		return Add(other);
	}
	
	Vector2& Vector2::operator-=(const Vector2 &other)
	{
		return Subtract(other);
	}
	
	Vector2& Vector2::operator*=(const float &num)
	{
		return Multiply(num);
	}
	
	Vector2& Vector2::operator/=(const float &num)
	{
		return Divide(num);
	}
	
	bool Vector2::operator==(const Vector2 &other)
	{
		return x == other.x && y == other.y;
	}
	
	bool Vector2::operator!=(const Vector2 &other)
	{
		return x != other.x || y != other.y;
	}
}
