#include "Vertex.hpp"

namespace atom
{
    Vertex::Vertex(const Vector3& p, const Vector2& uv, const Vector3& n, const Vector3& t)
    {
        this->position = p;
        this->texCoord = uv;
        this->normal = n;
        this->tangent = t;
    }
}
