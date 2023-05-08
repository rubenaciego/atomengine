#pragma once

#include <unordered_map>
#include <memory>

namespace atom
{
    class Mesh;
    class Vertex;

    class MeshManager
    {
    public:
        static std::shared_ptr<Mesh> CreateMesh(const std::string& filename, const std::string& name = "");
        static std::shared_ptr<Mesh> CreateMesh(Vertex* vertices, unsigned int numVerts,
            unsigned int* indices, unsigned int numIndices, const std::string& name);
        
        static std::shared_ptr<Mesh> GetMesh(const std::string& name);
        static void Flush();
        static void DeleteInstance(const std::string& name);
        
    private:
        MeshManager();
        
        static std::unordered_map<std::string, std::weak_ptr<Mesh>> meshes;
    };
}
