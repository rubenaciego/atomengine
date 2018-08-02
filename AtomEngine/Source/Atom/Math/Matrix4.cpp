#include <cstring>
#include <Atom/Math/Vector3.hpp>
#include <Atom/Math/Math.hpp>
#include <Atom/Math/Matrix4.hpp>

namespace atom
{
	Matrix4::Matrix4()
	{
		for (int i = 0; i < 16; i++)
			elements[i] = 0.0f;
	}
	
	Matrix4::Matrix4(float diagonal)
	{
		for (int i = 1; i < 15; i++)
			elements[i] = 0.0f;
	
		elements[0] = diagonal;
		elements[5] = diagonal;
		elements[10] = diagonal;
		elements[15] = diagonal;
	}
	
	Matrix4 Matrix4::Identity()
	{
		return Matrix4(1.0f);
	}
	
	Matrix4& Matrix4::Invert()
	{
		float temp[16];
	
		temp[0] = elements[5] * elements[10] * elements[15] -
			elements[5] * elements[11] * elements[14] -
			elements[9] * elements[6] * elements[15] +
			elements[9] * elements[7] * elements[14] +
			elements[13] * elements[6] * elements[11] -
			elements[13] * elements[7] * elements[10];
	
		temp[4] = -elements[4] * elements[10] * elements[15] +
			elements[4] * elements[11] * elements[14] +
			elements[8] * elements[6] * elements[15] -
			elements[8] * elements[7] * elements[14] -
			elements[12] * elements[6] * elements[11] +
			elements[12] * elements[7] * elements[10];
	
		temp[8] = elements[4] * elements[9] * elements[15] -
			elements[4] * elements[11] * elements[13] -
			elements[8] * elements[5] * elements[15] +
			elements[8] * elements[7] * elements[13] +
			elements[12] * elements[5] * elements[11] -
			elements[12] * elements[7] * elements[9];
	
		temp[12] = -elements[4] * elements[9] * elements[14] +
			elements[4] * elements[10] * elements[13] +
			elements[8] * elements[5] * elements[14] -
			elements[8] * elements[6] * elements[13] -
			elements[12] * elements[5] * elements[10] +
			elements[12] * elements[6] * elements[9];
	
		temp[1] = -elements[1] * elements[10] * elements[15] +
			elements[1] * elements[11] * elements[14] +
			elements[9] * elements[2] * elements[15] -
			elements[9] * elements[3] * elements[14] -
			elements[13] * elements[2] * elements[11] +
			elements[13] * elements[3] * elements[10];
	
		temp[5] = elements[0] * elements[10] * elements[15] -
			elements[0] * elements[11] * elements[14] -
			elements[8] * elements[2] * elements[15] +
			elements[8] * elements[3] * elements[14] +
			elements[12] * elements[2] * elements[11] -
			elements[12] * elements[3] * elements[10];
	
		temp[9] = -elements[0] * elements[9] * elements[15] +
			elements[0] * elements[11] * elements[13] +
			elements[8] * elements[1] * elements[15] -
			elements[8] * elements[3] * elements[13] -
			elements[12] * elements[1] * elements[11] +
			elements[12] * elements[3] * elements[9];
	
		temp[13] = elements[0] * elements[9] * elements[14] -
			elements[0] * elements[10] * elements[13] -
			elements[8] * elements[1] * elements[14] +
			elements[8] * elements[2] * elements[13] +
			elements[12] * elements[1] * elements[10] -
			elements[12] * elements[2] * elements[9];
	
		temp[2] = elements[1] * elements[6] * elements[15] -
			elements[1] * elements[7] * elements[14] -
			elements[5] * elements[2] * elements[15] +
			elements[5] * elements[3] * elements[14] +
			elements[13] * elements[2] * elements[7] -
			elements[13] * elements[3] * elements[6];
	
		temp[6] = -elements[0] * elements[6] * elements[15] +
			elements[0] * elements[7] * elements[14] +
			elements[4] * elements[2] * elements[15] -
			elements[4] * elements[3] * elements[14] -
			elements[12] * elements[2] * elements[7] +
			elements[12] * elements[3] * elements[6];
	
		temp[10] = elements[0] * elements[5] * elements[15] -
			elements[0] * elements[7] * elements[13] -
			elements[4] * elements[1] * elements[15] +
			elements[4] * elements[3] * elements[13] +
			elements[12] * elements[1] * elements[7] -
			elements[12] * elements[3] * elements[5];
	
		temp[14] = -elements[0] * elements[5] * elements[14] +
			elements[0] * elements[6] * elements[13] +
			elements[4] * elements[1] * elements[14] -
			elements[4] * elements[2] * elements[13] -
			elements[12] * elements[1] * elements[6] +
			elements[12] * elements[2] * elements[5];
	
		temp[3] = -elements[1] * elements[6] * elements[11] +
			elements[1] * elements[7] * elements[10] +
			elements[5] * elements[2] * elements[11] -
			elements[5] * elements[3] * elements[10] -
			elements[9] * elements[2] * elements[7] +
			elements[9] * elements[3] * elements[6];
	
		temp[7] = elements[0] * elements[6] * elements[11] -
			elements[0] * elements[7] * elements[10] -
			elements[4] * elements[2] * elements[11] +
			elements[4] * elements[3] * elements[10] +
			elements[8] * elements[2] * elements[7] -
			elements[8] * elements[3] * elements[6];
	
		temp[11] = -elements[0] * elements[5] * elements[11] +
			elements[0] * elements[7] * elements[9] +
			elements[4] * elements[1] * elements[11] -
			elements[4] * elements[3] * elements[9] -
			elements[8] * elements[1] * elements[7] +
			elements[8] * elements[3] * elements[5];
	
		temp[15] = elements[0] * elements[5] * elements[10] -
			elements[0] * elements[6] * elements[9] -
			elements[4] * elements[1] * elements[10] +
			elements[4] * elements[2] * elements[9] +
			elements[8] * elements[1] * elements[6] -
			elements[8] * elements[2] * elements[5];
	
		float determinant = 1.0f / (elements[0] * temp[0] + elements[1] * temp[4] + elements[2] * temp[8] + elements[3] * temp[12]);
	
		for (int i = 0; i < 16; i++)
			elements[i] = temp[i] * determinant;
	
		return *this;
	}
	
	Matrix4& Matrix4::Multiply(const Matrix4 &other)
	{
		float data[16];
	
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				float sum = 0.0f;
	
				for (int e = 0; e < 4; e++)
					sum += elements[x + e * 4] * other.elements[e + y * 4];
	
				data[x + y * 4] = sum;
			}
		}
	
		memcpy(elements, data, 16 * sizeof(float));
	
		return *this;
	}
	
	Vector3 Matrix4::Multiply(const Vector3 &other) const
	{
		return Vector3(columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x,
			columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y,
			columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z);
	}
	
	Vector4 Matrix4::Multiply(const Vector4 &other) const
	{
		return Vector4(columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x * other.w,
			columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y * other.w,
			columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z * other.w,
			columns[0].w * other.x + columns[1].w * other.y + columns[2].w * other.z + columns[3].w * other.w);
	}
	
	Matrix4 Matrix4::Orthographic(float left, float right, float bottom, float top, float near, float far)
	{
		Matrix4 result(1.0f);
	
		result.elements[0] = 2.0f / (right - left);
		result.elements[5] = 2.0f / (top - bottom);
		result.elements[10] = 2.0f / (near - far);
	
		result.elements[12] = (left + right) / (left - right);
		result.elements[13] = (bottom + top) / (bottom - top);
		result.elements[14] = (far + near) / (far - near);
	
		return result;
	}
	
	Matrix4 Matrix4::Perspective(float fov, float aspectRatio, float near, float far)
	{
		Matrix4 result(1.0f);
	
		float q = 1.0f / Math::Tan(Math::ToRadians(0.5f * fov));
		float a = q / aspectRatio;
	
		result.elements[0] = a;
		result.elements[5] = q;
		result.elements[10] = (near + far) / (near - far);
		result.elements[11] = -1.0f;
		result.elements[14] = (2.0f * near * far) / (near - far);
	
		return result;
	}
	
	Matrix4 Matrix4::Translation(const Vector3 &translation)
	{
		Matrix4 result(1.0f);
	
		result.elements[12] = translation.x;
		result.elements[13] = translation.y;
		result.elements[14] = translation.z;
	
		return result;
	}
	
	Matrix4 Matrix4::Scale(const Vector3 &scale)
	{
		Matrix4 result(1.0f);
	
		result.elements[0] = scale.x;
		result.elements[5] = scale.y;
		result.elements[10] = scale.z;
	
		return result;
	}
	
	Matrix4 Matrix4::Rotation(float angle, const Vector3 &axis)
	{
		Matrix4 result(1.0f);
	
		float r = Math::ToRadians(angle);
		float c = cos(r);
		float s = sin(r);
		float omc = 1.0f - c;
	
		result.elements[0 + 0 * 4] = axis.x * axis.x * omc + c;
		result.elements[0 + 1 * 4] = axis.y * axis.x * omc + axis.z * s;
		result.elements[0 + 2 * 4] = axis.x * axis.z * omc - axis.y * s;
	
		result.elements[1 + 0 * 4] = axis.x * axis.y * omc - axis.z * s;
		result.elements[1 + 1 * 4] = axis.y * axis.y * omc + c;
		result.elements[1 + 2 * 4] = axis.y * axis.z * omc + axis.x * s;
	
		result.elements[2 + 0 * 4] = axis.x * axis.z * omc + axis.y * s;
		result.elements[2 + 1 * 4] = axis.y * axis.z * omc - axis.x * s;
		result.elements[2 + 2 * 4] = axis.z * axis.z * omc + c;
	
		return result;
	}
	
	Matrix4& Matrix4::operator*=(const Matrix4 &other)
	{
		return Multiply(other);
	}
	
	Matrix4 operator*(Matrix4 left, const Matrix4 &right)
	{
		return left.Multiply(right);
	}
	
	Vector3 operator*(const Matrix4 &left, const Vector3 &right)
	{
		return left.Multiply(right);
	}
	
	Vector4 operator*(const Matrix4 &left, const Vector4&right)
	{
		return left.Multiply(right);
	}
}
