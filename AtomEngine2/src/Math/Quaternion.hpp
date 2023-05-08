#pragma once

#include <Math/Vector3.hpp>
#include <Math/Matrix4.hpp>

namespace atom
{
    class Quaternion
    {
    public:
        float x, y, z, w;

        Quaternion(float x = 0, float y = 0, float z = 0, float w = 1);
        Quaternion(const Vector3& axis, float angle);

        void Normalize();
        Quaternion Normalized() const;

        float Dot(const Quaternion& r) const;
        Quaternion NLerp(const Quaternion& dest, float lerpFactor, bool shortest);
        Quaternion Conjugate() const;
        Vector3 GetForward() const;
        Vector3 GetBack() const;
        Vector3 GetUp() const;
        Vector3 GetDown() const;
        Vector3 GetRight() const;
        Vector3 GetLeft() const;
        Matrix4 ToRotationMatrix() const;

        Quaternion operator*(const Quaternion& r) const;
        Quaternion operator*(const Vector3& v) const;

        Quaternion operator+(const Quaternion& r) const;
		Quaternion operator-(const Quaternion& r) const;
		Quaternion operator*(float f) const;
		Quaternion operator/(float f) const;

        Quaternion& operator+=(const Quaternion& r);
		Quaternion& operator-=(const Quaternion& r);
		Quaternion& operator*=(float f);
		Quaternion& operator/=(float f);

        bool operator==(const Quaternion& r) const;
		bool operator!=(const Quaternion& r) const;
    };
}
