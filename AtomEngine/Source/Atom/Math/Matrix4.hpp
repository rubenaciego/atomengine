#pragma once

#include <Atom/Math/Vector4.hpp>

namespace Atom
{
	struct Vector3;

	struct Matrix4
	{
	public:
	
		union
		{
			float elements[16];
			Vector4 columns[4];
		};
	
		Matrix4();
		Matrix4(float diagonal);
	
		Matrix4& Invert();
		Matrix4& Multiply(const Matrix4 &other);
		Vector3 Multiply(const Vector3 &other) const;
		Vector4 Multiply(const Vector4 &other) const;
	
		Matrix4& operator*=(const Matrix4 &other);
		friend Matrix4 operator*(Matrix4 left, const Matrix4 &right);
		friend Vector3 operator*(const Matrix4 &left, const Vector3 &right);
		friend Vector4 operator*(const Matrix4 &left, const Vector4 &right);
	
		static Matrix4 Identity();
		static Matrix4 Orthographic(float left, float right, float bottom, float top, float near, float far);
		static Matrix4 Perspective(float fov, float aspectRatio, float near, float far);
		
		static Matrix4 Translation(const Vector3 &translation);
		static Matrix4 Rotation(float angle, const Vector3 &axis);
		static Matrix4 Scale(const Vector3 &scale);
	
		inline float GetElement(const int row, const int col) { return elements[row + col * 4]; }
		inline void SetElement(float val, const int row, const int col) { elements[row + col * 4] = val; }
	};
}
