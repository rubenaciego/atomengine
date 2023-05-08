#pragma once

#include <Math/Vector3.hpp>

namespace atom
{
	class Matrix4 
	{
	public:
		Matrix4();

		Matrix4& InitIdentity();
		Matrix4& InitScale(float x, float y, float z);
		Matrix4& InitRotation(float x, float y, float z);
		Matrix4& InitRotation(const Vector3& target, const Vector3& up);
		Matrix4& InitRotation(const Vector3& forward, const Vector3& up, const Vector3& right);
		Matrix4& InitTranslation(float x, float y, float z);
		Matrix4& InitPerspective(float fov, float ar, float zNear, float zFar);
		Matrix4& InitOrthographic(float left, float right, float bottom, float top, float near, float far);

		Vector3 Transform(const Vector3& r);

		Matrix4 operator*(const Matrix4& right) const;
		const float* operator[](int index) const;
		float* operator[](int index);

	private:
		float m[4][4];
	};
}
