#pragma once

#include <Math/Vector3.hpp>
#include <Math/Vector2.hpp>
#include <ResourceManagement/IndexedModel.hpp>
#include <vector>
#include <string>

namespace atom
{
    struct OBJIndex
    {
        unsigned int vertexIndex;
        unsigned int uvIndex;
        unsigned int normalIndex;
        
        bool operator==(const OBJIndex& r) const;
    };

    class OBJModel
    {
    public:
        std::vector<OBJIndex> OBJIndices;
        std::vector<Vector3> vertices;
        std::vector<Vector2> uvs;
        std::vector<Vector3> normals;
        bool hasUVs;
        bool hasNormals;
        
        OBJModel(const std::string& fileName);
        
        IndexedModel ToIndexedModel();
        
    private:
        void CreateOBJFace(const std::string& line);
        
        Vector2 ParseOBJVec2(const std::string& line);
        Vector3 ParseOBJVec3(const std::string& line);
        OBJIndex ParseOBJIndex(const std::string& token, bool* hasUVs, bool* hasNormals);
    };
}

template <>struct std::hash<atom::OBJIndex>
{
    std::size_t operator()(const atom::OBJIndex& index) const
    {
        const int BASE = 17;
        const int MULT = 31;

        std::size_t result = BASE;

        result = MULT * result + index.vertexIndex;
        result = MULT * result + index.uvIndex;
        result = MULT * result + index.normalIndex;

        return result;
    }
};
