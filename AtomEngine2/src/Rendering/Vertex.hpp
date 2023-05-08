#pragma once

#include <Math/Vector3.hpp>
#include <Math/Vector2.hpp>

namespace atom
{
    class Vertex
    {
    public:
        Vector3 position;
        Vector2 texCoord;
        Vector3 normal;
        Vector3 tangent;

        Vertex(const Vector3& p = Vector3(), const Vector2& uv = Vector2(),
            const Vector3& n = Vector3(), const Vector3& t = Vector3());
    };
}
