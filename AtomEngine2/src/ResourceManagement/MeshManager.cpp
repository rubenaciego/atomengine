#include "MeshManager.hpp"
#include <Rendering/Mesh.hpp>
#include <Debug/Log.hpp>

namespace atom
{
    std::unordered_map<std::string, std::weak_ptr<Mesh>> MeshManager::meshes;

    std::shared_ptr<Mesh> MeshManager::CreateMesh(const std::string& filename, const std::string& name)
    {
        const std::string& s = name.length() ? name : filename;

        try
        {
            std::shared_ptr<Mesh> ptr = meshes.at(s).lock();
            return ptr;
        }
        catch (const std::out_of_range& e)
        {
            std::shared_ptr<Mesh> mesh(new Mesh(filename));
            meshes[s] = mesh;
            mesh->name = s;

            return mesh;
        }
    }

    std::shared_ptr<Mesh> MeshManager::CreateMesh(Vertex* vertices, unsigned int numVerts,
        unsigned int* indices, unsigned int numIndices, const std::string& name)
    {
        try
        {
            std::shared_ptr<Mesh> ptr = meshes.at(name).lock();
            ATOM_CORE_WARN("[Atom]: Warning, atempting to creating existing mesh: %s\n", name.c_str());
            return ptr;
        }
        catch (const std::out_of_range& e)
        {
            std::shared_ptr<Mesh> mesh(new Mesh(vertices, numVerts, indices, numIndices));
            meshes[name] = mesh;
            mesh->name = name; 

            return mesh;
        }
    }

    std::shared_ptr<Mesh> MeshManager::GetMesh(const std::string& name)
    {
        return meshes.at(name).lock();
    }

    void MeshManager::Flush()
    {
        meshes.clear();
    }

    void MeshManager::DeleteInstance(const std::string& name)
    {
        meshes.erase(name);
    }
}
