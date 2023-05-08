#include "Vector2.hpp"
#include <cmath>
#include <algorithm>

namespace atom
{
	const Vector2 Vector2::UP(0, 1);
    const Vector2 Vector2::DOWN(0, -1);
    const Vector2 Vector2::LEFT(-1, 0);
    const Vector2 Vector2::RIGHT(1, 0);
    const Vector2 Vector2::ONE(1, 1);
    const Vector2 Vector2::ZERO(0, 0);

	Vector2::Vector2(float x, float y)
    {
    	this->x = x;
        this->y = y;
    }

	float Vector2::Length() const
	{
		return sqrtf(x * x + y * y);
	}

	float Vector2::LengthSq() const
	{
		return x * x + y * y;
	}

	float Vector2::Dot(const Vector2& v) const
	{
		return x * v.x + y * v.y;
	}

	float Vector2::Cross(const Vector2& v) const
	{
		return x * v.y - y * v.x;
	}

	float Vector2::Max() const
	{
		return std::max(x, y);
	}

	Vector2 Vector2::Rotate(float angle) const
	{
		const float sn = sinf(angle);
		const float cs = cosf(angle);

		return Vector2(x * cs - y * sn, x * sn + y * cs);
	}

	Vector2 Vector2::Lerp(const Vector2& dest, float factor) const
    {
        return (dest - *this) * factor + *this; 
    }

	Vector2& Vector2::Normalize()
	{
		const float l = Length();

		x /= l;
		y /= l;
		
		return *this;
	}

	Vector2 Vector2::Normalized() const
	{
		const float l = Length();

		return Vector2(x / l, y / l);
	}

	Vector2& Vector2::operator+=(const Vector2& r)
	{
		x += r.x;
		y += r.y;

		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& r)
	{
		x -= r.x;
		y -= r.y;

		return *this;
	}

	Vector2& Vector2::operator*=(float f)
	{
		x *= f;
		y *= f;

		return *this;
	}

	Vector2& Vector2::operator/=(float f)
	{
		x /= f;
		y /= f;

		return *this;
	}

	Vector2& Vector2::operator*=(const Vector2& v)
	{
		x *= v.x;
		y *= v.y;

		return *this;
	}

	Vector2& Vector2::operator/=(const Vector2& v)
	{
		x /= v.x;
		y /= v.y;

		return *this;
	}

	Vector2 Vector2::operator+(const Vector2& r) const 
	{
		return Vector2(x + r.x, y + r.y);
	}

	Vector2 Vector2::operator-(const Vector2& r) const 
	{
		return Vector2(x - r.x, y - r.y);
	}

	Vector2 Vector2::operator*(float f) const
	{
		return Vector2(x * f, y * f);
	}

	Vector2 Vector2::operator/(float f) const 
	{
		return Vector2(x / f, y / f);
	}

	Vector2 Vector2::operator*(const Vector2& v) const
	{
		return Vector2(x * v.x, y * v.y);
	}

	Vector2 Vector2::operator/(const Vector2& v) const 
	{
		return Vector2(x / v.x, y / v.y);
	}

	bool Vector2::operator==(const Vector2& r) const
	{
		return x == r.x && y == r.y;
	}

	bool Vector2::operator!=(const Vector2& r) const
	{
		return x != r.x || y != r.y;
	}
}
