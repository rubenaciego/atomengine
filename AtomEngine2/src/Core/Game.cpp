#include "Game.hpp"
#include <Rendering/Renderer3D.hpp>

namespace atom
{
    void Game::Update()
    {
        root.Update();
    }

    void Game::Render(Renderer3D& renderer3D)
    {
        renderer3D.Render(root);
    }

    void Game::AddGameObject(GameObject* gameObject)
    {
        root.AddChild(gameObject);
    }
}
