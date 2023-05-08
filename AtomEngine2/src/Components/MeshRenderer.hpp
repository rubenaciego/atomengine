#pragma once

#include <Components/GameComponent.hpp>
#include <Rendering/Material.hpp>
#include <memory>

namespace atom
{
    class Mesh;

    class MeshRenderer : public GameComponent
    {
    private:
        std::shared_ptr<Mesh> mesh;
        Material material;

    public:
        MeshRenderer(std::shared_ptr<Mesh> mesh, Material material);
        
        void Render(std::shared_ptr<Shader> shader, Renderer3D& renderer3D) override;
    };
}
