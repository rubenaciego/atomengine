#include <Atom/Math/Vector4.hpp>

namespace atom
{
	Vector4::Vector4()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}
	
	Vector4::Vector4(const float& x, const float& y, const float& z, const float &w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
	
	Vector4& Vector4::Add(const Vector4 &other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
	
		return *this;
	}
	
	Vector4& Vector4::Subtract(const Vector4 &other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
	
		return *this;
	}
	
	Vector4& Vector4::Multiply(const float &num)
	{
		x *= num;
		y *= num;
		z *= num;
		w *= num;
	
		return *this;
	}
	
	Vector4& Vector4::Divide(const float &num)
	{
		x /= num;
		y /= num;
		z /= num;
		w /= num;
	
		return *this;
	}
	
	Vector4 operator+(Vector4 left, const Vector4 &right)
	{
		return left.Add(right);
	}
	
	Vector4 operator-(Vector4 left, const Vector4 &right)
	{
		return left.Subtract(right);
	}
	
	Vector4 operator*(Vector4 vector, const float &num)
	{
		return vector.Multiply(num);
	}
	
	Vector4 operator/(Vector4 vector, const float &num)
	{
		return vector.Divide(num);
	}
	
	Vector4& Vector4::operator+=(const Vector4 &other)
	{
		return Add(other);
	}
	
	Vector4& Vector4::operator-=(const Vector4 &other)
	{
		return Subtract(other);
	}
	
	Vector4& Vector4::operator*=(const float &num)
	{
		return Multiply(num);
	}
	
	Vector4& Vector4::operator/=(const float &num)
	{
		return Divide(num);
	}
	
	bool Vector4::operator==(const Vector4 &other)
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}
	
	bool Vector4::operator!=(const Vector4 &other)
	{
		return x != other.x || y != other.y || z != other.z || w != other.w;
	}
}
