#pragma once

#include <Core/Transform.hpp>
#include <list>
#include <memory>

namespace atom
{
    class GameComponent;
    class Shader;
    class Renderer3D;
    class CoreEngine;

    class GameObject
    {
    private:
        std::list<GameObject*> children;
        std::list<GameComponent*> components;
        CoreEngine* engine;

    public:
        GameObject();
        virtual ~GameObject();

        virtual void Update();
        virtual void Render(std::shared_ptr<Shader> shader, Renderer3D& renderer3D);

        std::list<GameObject*> GetChildrenRecursively() const;
        
        void AddChild(GameObject* child);
        void AddComponent(GameComponent* component);
        
        Transform transform;
        GameObject* parent;

        friend class CoreEngine;
    };
}
