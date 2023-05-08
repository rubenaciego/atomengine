#pragma once

#include <memory>

namespace atom
{
    class Shader;
    class CoreEngine;
    class Renderer3D;
    class GameObject;
    
    class GameComponent
    {
    public:
        virtual ~GameComponent() {}
        virtual void Update() {}
        virtual void Render(std::shared_ptr<Shader> shader, Renderer3D& renderer3D) {}
        virtual void AddToEngine(CoreEngine& engine) {}

        GameObject* parent;
    };
}
