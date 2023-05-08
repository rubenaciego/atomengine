#pragma once

#include <Math/Vector2.hpp>
#include <Math/Vector3.hpp>
#include <vector>

namespace atom
{
    class IndexedModel
    {
    public:
        std::vector<Vector3> positions;
        std::vector<Vector2> texCoords;
        std::vector<Vector3> normals;
        std::vector<unsigned int> indices;
        std::vector<Vector3> tangents;
        
        void CalcNormals();
        void CalcTangentSpace();
    };
}
