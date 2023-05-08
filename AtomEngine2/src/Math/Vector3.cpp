#include "Vector3.hpp"
#include <Math/Quaternion.hpp>
#include <Math/Vector2.hpp>
#include <cmath>
#include <algorithm>

namespace atom
{
    const Vector3 Vector3::UP(0, 1, 0);
    const Vector3 Vector3::DOWN(0, -1, 0);
    const Vector3 Vector3::LEFT(-1, 0, 0);
    const Vector3 Vector3::RIGHT(1, 0, 0);
    const Vector3 Vector3::FORWARD(0, 0, 1);
    const Vector3 Vector3::BACK(0, 0, -1);
    const Vector3 Vector3::ONE(1, 1, 1);
    const Vector3 Vector3::ZERO(0, 0, 0);

    Vector3::Vector3(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    float Vector3::Length() const
    {
        return sqrtf(x * x + y * y + z * z);
    }

    float Vector3::LengthSq() const
    {
        return x * x + y * y + z * z;
    }

    float Vector3::Dot(const Vector3& v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    float Vector3::Max() const
    {
        return std::max(x, std::max(y, z));
    }

    Vector3 Vector3::Cross(const Vector3& v) const
    {
        return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }

    Vector3& Vector3::Normalize()
    {
        const float l = Length();

        x /= l;
        y /= l;
        z /= l;

        return *this;
    }

    Vector3 Vector3::Normalized() const
    {
        const float l = Length();

        return Vector3(x / l, y / l, z / l);
    }

    Vector3 Vector3::Rotate(const Vector3& axis, float angle) const
    {
        Quaternion rotation(axis, angle);

        return Rotate(rotation);
    }

    Vector3 Vector3::Rotate(const Quaternion& q) const
    {
        Quaternion conjugate = q.Conjugate();
        Quaternion w = q * (*this) * conjugate;

        Vector3 ret(w.x, w.y, w.z);

        return ret;
    }

    Vector3 Vector3::Lerp(const Vector3& dest, float factor) const
    {
        return (dest - *this) * factor + *this; 
    }

    Vector2 Vector3::GetXY() const { return Vector2(x, y); }
	Vector2 Vector3::GetYZ() const { return Vector2(y, z); }
	Vector2 Vector3::GetZX() const { return Vector2(z, x); }
	Vector2 Vector3::GetYX() const { return Vector2(y, x); }
	Vector2 Vector3::GetZY() const { return Vector2(z, y); }
	Vector2 Vector3::GetXZ() const { return Vector2(x, z); }

    Vector3& Vector3::operator+=(const Vector3& r)
    {
        x += r.x;
        y += r.y;
        z += r.z;

        return *this;
    }

    Vector3& Vector3::operator-=(const Vector3& r)
    {
        x -= r.x;
        y -= r.y;
        z -= r.z;

        return *this;
    }

    Vector3& Vector3::operator*=(float f)
    {
        x *= f;
        y *= f;
        z *= f;

        return *this;
    }

    Vector3& Vector3::operator/=(float f)
    {
        x /= f;
        y /= f;
        z /= f;

        return *this;
    }

    Vector3& Vector3::operator*=(const Vector3& v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;

        return *this;
    }

    Vector3& Vector3::operator/=(const Vector3& v)
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;

        return *this;
    }

    Vector3 Vector3::operator+(const Vector3& r) const 
    {
        return Vector3(x + r.x, y + r.y, z + r.z);
    }

    Vector3 Vector3::operator-(const Vector3& r) const 
    {
        return Vector3(x - r.x, y - r.y, z - r.z);
    }

    Vector3 Vector3::operator*(float f) const
    {
        return Vector3(x * f, y * f, z * f);
    }

    Vector3 Vector3::operator/(float f) const 
    {
        return Vector3(x / f, y / f, z / f);
    }

	Vector3 Vector3::operator*(const Vector3& v) const
    {
        return Vector3(x * v.x, y * v.y, z * v.z);
    }

    Vector3 Vector3::operator/(const Vector3& v) const
    {
        return Vector3(x / v.x, y / v.y, z / v.z);
    }

    bool Vector3::operator==(const Vector3& r) const
    {
        return x == r.x && y == r.y && z == r.z;
    }

    bool Vector3::operator!=(const Vector3& r) const
    {
        return x != r.x || y != r.y || z != r.z;
    }
}
