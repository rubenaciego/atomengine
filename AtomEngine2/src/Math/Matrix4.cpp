#include "Matrix4.hpp"
#include <cmath>

namespace atom
{
    Matrix4::Matrix4()
    {
        InitIdentity();
    }

    Matrix4& Matrix4::InitIdentity()
    {
        m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
        m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
        m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;     
        m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;

        return *this;
    }

    Matrix4& Matrix4::InitScale(float x, float y, float z)
    {
        m[0][0] = x;      m[0][1] = 0.0f;   m[0][2] = 0.0f;   m[0][3] = 0.0f;
        m[1][0] = 0.0f;   m[1][1] = y;      m[1][2] = 0.0f;   m[1][3] = 0.0f;
        m[2][0] = 0.0f;   m[2][1] = 0.0f;   m[2][2] = z;      m[2][3] = 0.0f;
        m[3][0] = 0.0f;   m[3][1] = 0.0f;   m[3][2] = 0.0f;   m[3][3] = 1.0f;

        return *this;
    }

    Matrix4& Matrix4::InitRotation(float x, float y, float z)
    {
        Matrix4 rx, ry, rz;

        rx.m[0][0] = 1.0f; rx.m[0][1] = 0.0f;    rx.m[0][2] = 0.0f;     rx.m[0][3] = 0.0f;
        rx.m[1][0] = 0.0f; rx.m[1][1] = cosf(x); rx.m[1][2] = -sinf(x); rx.m[1][3] = 0.0f;
        rx.m[2][0] = 0.0f; rx.m[2][1] = sinf(x); rx.m[2][2] = cosf(x);  rx.m[2][3] = 0.0f;
        rx.m[3][0] = 0.0f; rx.m[3][1] = 0.0f;    rx.m[3][2] = 0.0f;     rx.m[3][3] = 1.0f;

        ry.m[0][0] = cosf(y); ry.m[0][1] = 0.0f; ry.m[0][2] = -sinf(y); ry.m[0][3] = 0.0f;
        ry.m[1][0] = 0.0f;    ry.m[1][1] = 1.0f; ry.m[1][2] = 0.0f;     ry.m[1][3] = 0.0f;
        ry.m[2][0] = sinf(y); ry.m[2][1] = 0.0f; ry.m[2][2] = cosf(y);  ry.m[2][3] = 0.0f;
        ry.m[3][0] = 0.0f;    ry.m[3][1] = 0.0f; ry.m[3][2] = 0.0f;     ry.m[3][3] = 1.0f;

        rz.m[0][0] = cosf(z); rz.m[0][1] = -sinf(z); rz.m[0][2] = 0.0f; rz.m[0][3] = 0.0f;
        rz.m[1][0] = sinf(z); rz.m[1][1] = cosf(z);  rz.m[1][2] = 0.0f; rz.m[1][3] = 0.0f;
        rz.m[2][0] = 0.0f;    rz.m[2][1] = 0.0f;     rz.m[2][2] = 1.0f; rz.m[2][3] = 0.0f;
        rz.m[3][0] = 0.0f;    rz.m[3][1] = 0.0f;     rz.m[3][2] = 0.0f; rz.m[3][3] = 1.0f;

        *this = rz * ry * rx;
        
        return *this;
    }

    Matrix4& Matrix4::InitRotation(const Vector3& forward, const Vector3& up)
    {
        Vector3 f = forward.Normalized();
        Vector3 u = up.Normalized();
        Vector3 r = up.Cross(f);
        
        InitRotation(f, u, r);

        return *this;
    }

    Matrix4& Matrix4::InitRotation(const Vector3& forward, const Vector3& up, const Vector3& right)
    {
        Vector3 f = forward;
        Vector3 r = right;
        Vector3 u = up;
        
        m[0][0] = r.x;   m[0][1] = r.y;   m[0][2] = r.z;   m[0][3] = 0.0f;
        m[1][0] = u.x;   m[1][1] = u.y;   m[1][2] = u.z;   m[1][3] = 0.0f;
        m[2][0] = f.x;   m[2][1] = f.y;   m[2][2] = f.z;   m[2][3] = 0.0f;
        m[3][0] = 0.0f;  m[3][1] = 0.0f;  m[3][2] = 0.0f;  m[3][3] = 1.0f;

        return *this;
    }

    Matrix4& Matrix4::InitTranslation(float x, float y, float z)
    {
        m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = x;
        m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = y;
        m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = z;
        m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;

        return *this;
    }

    Matrix4& Matrix4::InitPerspective(float fov, float ar, float zNear, float zFar)
    {
        const float zRange = zNear - zFar;
        const float tanHalfFOV = tanf(fov / 2.0f);

        m[0][0] = 1.0f / (tanHalfFOV * ar); m[0][1] = 0.0f;              m[0][2] = 0.0f;                     m[0][3] = 0.0;
        m[1][0] = 0.0f;                     m[1][1] = 1.0f / tanHalfFOV; m[1][2] = 0.0f;                     m[1][3] = 0.0;
        m[2][0] = 0.0f;                     m[2][1] = 0.0f;              m[2][2] = (-zNear - zFar) / zRange; m[2][3] = 2.0f * zFar * zNear / zRange;
        m[3][0] = 0.0f;                     m[3][1] = 0.0f;              m[3][2] = 1.0f;                     m[3][3] = 0.0;

        return *this;
    }

    Matrix4& Matrix4::InitOrthographic(float left, float right, float bottom, float top, float near, float far)
    {
        InitIdentity();
	
		m[0][0] = 2.0f / (right - left);
		m[1][1] = 2.0f / (top - bottom);
		m[2][2] = 2.0f / (near - far);
	
		m[4][0] = (left + right) / (left - right);
		m[4][1] = (bottom + top) / (bottom - top);
		m[4][2] = (far + near) / (far - near);

        return *this;
    }

    Vector3 Matrix4::Transform(const Vector3& r)
    {
        return Vector3(m[0][0] * r.x + m[0][1] * r.y + m[0][2] * r.z + m[0][3],
                       m[1][0] * r.x + m[1][1] * r.y + m[1][2] * r.z + m[1][3],
                       m[2][0] * r.x + m[2][1] * r.y + m[2][2] * r.z + m[2][3]);
    }

    Matrix4 Matrix4::operator*(const Matrix4& right) const
    {
        Matrix4 ret;

        for (unsigned int i = 0 ; i < 4 ; i++) 
        {
            for (unsigned int j = 0 ; j < 4 ; j++) 
            {
                ret.m[i][j] = m[i][0] * right[0][j] +
                    m[i][1] * right[1][j] +
                    m[i][2] * right[2][j] +
                    m[i][3] * right[3][j];
            }
        }
        
        return ret;
    }

    const float* Matrix4::operator[](int index) const
    {
        return m[index];
    }

    float* Matrix4::operator[](int index)
    {
        return m[index];
    }
}
