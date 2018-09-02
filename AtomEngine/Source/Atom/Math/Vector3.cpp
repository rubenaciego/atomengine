#include <Atom/Math/Vector3.hpp>

namespace Atom
{
	Vector3::Vector3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	
	Vector3::Vector3(const float& x, const float& y, const float &z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	
	Vector3& Vector3::Add(const Vector3 &other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
	
		return *this;
	}
	
	Vector3& Vector3::Subtract(const Vector3 &other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
	
		return *this;
	}
	
	Vector3& Vector3::Multiply(const float &num)
	{
		x *= num;
		y *= num;
		z *= num;
	
		return *this;
	}
	
	Vector3& Vector3::Divide(const float &num)
	{
		x /= num;
		y /= num;
		z /= num;
	
		return *this;
	}
	
	Vector3 operator+(Vector3 left, const Vector3 &right)
	{
		return left.Add(right);
	}
	
	Vector3 operator-(Vector3 left, const Vector3 &right)
	{
		return left.Subtract(right);
	}
	
	Vector3 operator*(Vector3 vector, const float &num)
	{
		return vector.Multiply(num);
	}
	
	Vector3 operator/(Vector3 vector, const float &num)
	{
		return vector.Divide(num);
	}
	
	Vector3& Vector3::operator+=(const Vector3 &other)
	{
		return Add(other);
	}
	
	Vector3& Vector3::operator-=(const Vector3 &other)
	{
		return Subtract(other);
	}
	
	Vector3& Vector3::operator*=(const float &num)
	{
		return Multiply(num);
	}
	
	Vector3& Vector3::operator/=(const float &num)
	{
		return Divide(num);
	}
	
	bool Vector3::operator==(const Vector3 &other)
	{
		return x == other.x && y == other.y && z == other.z;
	}
	
	bool Vector3::operator!=(const Vector3 &other)
	{
		return x != other.x || y != other.y || z != other.z;
	}
}
