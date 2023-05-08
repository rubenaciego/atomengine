#pragma once

namespace atom
{
    class Vector2
    {
    public:
        static const Vector2 UP;
		static const Vector2 DOWN;
		static const Vector2 LEFT;
		static const Vector2 RIGHT;
		static const Vector2 ONE;
		static const Vector2 ZERO;

        float x, y;

        Vector2(float x = 0.0f, float y = 0.0f);

        float Length() const;
		float LengthSq() const;
		float Dot(const Vector2& v) const;
        float Cross(const Vector2& v) const;
        float Max() const;

		Vector2 Rotate(float angle) const;
        Vector2 Lerp(const Vector2& dist, float factor) const;

		Vector2& Normalize();
		Vector2 Normalized() const;

        Vector2& operator+=(const Vector2& r);
        Vector2& operator-=(const Vector2& r);
        Vector2& operator*=(float f);
        Vector2& operator/=(float f);
        Vector2& operator*=(const Vector2& v);
        Vector2& operator/=(const Vector2& v);

        Vector2 operator+(const Vector2& r) const;
        Vector2 operator-(const Vector2& r) const;
        Vector2 operator*(float f) const;
        Vector2 operator/(float f) const;
        Vector2 operator*(const Vector2& v) const;
        Vector2 operator/(const Vector2& v) const;

        bool operator==(const Vector2& r) const;
        bool operator!=(const Vector2& r) const;
    };
}
