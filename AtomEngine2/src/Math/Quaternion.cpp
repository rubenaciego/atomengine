#include "Quaternion.hpp"
#include <cmath>

namespace atom
{
    Quaternion::Quaternion(float x, float y, float z, float w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    Quaternion::Quaternion(const Vector3& axis, float angle)
    {
        const float sinHalfAngle = sinf(angle / 2.0f);
        const float cosHalfAngle = cosf(angle / 2.0f);

        x = axis.x * sinHalfAngle;
        y = axis.y * sinHalfAngle;
        z = axis.z * sinHalfAngle;
        w = cosHalfAngle;
    }

    void Quaternion::Normalize()
    {
        float length = sqrtf(x * x + y * y + z * z + w * w);
        *this /= length;
    }

    Quaternion Quaternion::Normalized() const
    {
        float length = sqrtf(x * x + y * y + z * z + w * w);
        return *this / length;
    }

    Quaternion Quaternion::NLerp(const Quaternion& dest, float lerpFactor, bool shortest)
    {
        Quaternion newDest = dest;

        if (shortest && Dot(dest) < 0)
            newDest *= -1.0f;

        return ((newDest - *this) * lerpFactor + *this).Normalized();
    }

    float Quaternion::Dot(const Quaternion& r) const
    {
        return x * r.x + y * r.y + z * r.z + w * r.w;
    }

    Quaternion Quaternion::Conjugate() const
    {
        return Quaternion(-x, -y, -z, w);
    }

    Vector3 Quaternion::GetForward() const
	{
		return Vector3::FORWARD.Rotate(*this);
	}

	Vector3 Quaternion::GetBack() const
	{
        return Vector3::BACK.Rotate(*this);
	}
	
	Vector3 Quaternion::GetUp() const
	{
        return Vector3::UP.Rotate(*this);
	}
	
	Vector3 Quaternion::GetDown() const
	{
        return Vector3::DOWN.Rotate(*this);
	}
	
	Vector3 Quaternion::GetRight() const
	{
        return Vector3::RIGHT.Rotate(*this);
	}
	
	Vector3 Quaternion::GetLeft() const
	{
        return Vector3::LEFT.Rotate(*this);
    }

    Matrix4 Quaternion::ToRotationMatrix() const
    {
        Matrix4 m;
        Vector3 f(2.0f * (x * z - w * y), 2.0f * (y * z + w * x), 1.0f - 2.0f * (x * x + y * y));
        Vector3 u(2.0f * (x * y + w * z), 1.0f - 2.0f * (x * x + z * z), 2.0f * (y * z - w * x));
        Vector3 r(1.0f - 2.0f * (y * y + z * z), 2.0f * (x * y - w * z), 2.0f * (x * z + w * y));
        m.InitRotation(f, u, r);

        return m;
    }

    Quaternion Quaternion::operator+(const Quaternion& r) const
    {
        return Quaternion(x + r.x, y + r.y, z + r.z, w + r.w);
    }

	Quaternion Quaternion::operator-(const Quaternion& r) const
    {
        return Quaternion(x - r.x, y - r.y, z - r.z, w - r.w);
    }

	Quaternion Quaternion::operator*(float f) const
    {
        return Quaternion(x * f, y * f, z * f, w * f);
    }

	Quaternion Quaternion::operator/(float f) const
    {
        return Quaternion(x / f, y / f, z / f, w / f);
    }

    Quaternion& Quaternion::operator+=(const Quaternion& r)
    {
        x += r.x;
        y += r.y;
        z += r.z;
        w += r.w;

        return *this;
    }

	Quaternion& Quaternion::operator-=(const Quaternion& r)
    {
        x -= r.x;
        y -= r.y;
        z -= r.z;
        w -= r.w;

        return *this;
    }

	Quaternion& Quaternion::operator*=(float f)
    {
        x *= f;
        y *= f;
        z *= f;
        w *= f;

        return *this;
    }

	Quaternion& Quaternion::operator/=(float f)
    {
        x /= f;
        y /= f;
        z /= f;
        w /= f;

        return *this;
    }

    Quaternion Quaternion::operator*(const Quaternion& r) const
    {
        const float _w = (w * r.w) - (x * r.x) - (y * r.y) - (z * r.z);
        const float _x = (x * r.w) + (w * r.x) + (y * r.z) - (z * r.y);
        const float _y = (y * r.w) + (w * r.y) + (z * r.x) - (x * r.z);
        const float _z = (z * r.w) + (w * r.z) + (x * r.y) - (y * r.x);

        return Quaternion(_x, _y, _z, _w);
    }

    Quaternion Quaternion::operator*(const Vector3& v) const
    {
        const float _w = - (x * v.x) - (y * v.y) - (z * v.z);
        const float _x =   (w * v.x) + (y * v.z) - (z * v.y);
        const float _y =   (w * v.y) + (z * v.x) - (x * v.z);
        const float _z =   (w * v.z) + (x * v.y) - (y * v.x);

        return Quaternion(_x, _y, _z, _w);
    }

    bool Quaternion::operator==(const Quaternion& r) const
    {
        return x == r.x && y == r.y && z == r.z && w == r.w;
    }

    bool Quaternion::operator!=(const Quaternion& r) const
    {
        return x != r.x || y != r.y || z != r.z || w != r.w;
    }
}
