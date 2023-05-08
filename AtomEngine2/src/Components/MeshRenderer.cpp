#include "MeshRenderer.hpp"
#include <Core/Transform.hpp>
#include <Core/GameObject.hpp>
#include <Rendering/Shader.hpp>
#include <Rendering/Mesh.hpp>

namespace atom
{
    MeshRenderer::MeshRenderer(std::shared_ptr<Mesh> mesh, Material material)
    {
        this->mesh = mesh;
        this->material = material;
    }
        
    void MeshRenderer::Render(std::shared_ptr<Shader> shader, Renderer3D& renderer3D)
    {
        shader->Bind();
        shader->UpdateUniforms(parent->transform, material, renderer3D);
        
        mesh->Draw();
    }
}
