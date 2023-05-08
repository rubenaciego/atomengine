#pragma once

#include <Core/GameObject.hpp>

namespace atom
{
    class CoreEngine;
    class Renderer3D;
    
    class Game
    {
    public:
        virtual ~Game() {}
        virtual const char* GetName() = 0;
        virtual void Start() {}
        virtual void Stop() {}
        virtual void Update();
        void Render(Renderer3D& renderer3D);
        void AddGameObject(GameObject* gameObject);

    protected:
        CoreEngine* engine;
        GameObject root;

        friend class CoreEngine;
    };
}
