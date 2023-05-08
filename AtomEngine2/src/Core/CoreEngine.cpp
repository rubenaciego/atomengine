#include "CoreEngine.hpp"
#include <Core/Game.hpp>
#include <Time/Time.hpp>
#include <Input/Input.hpp>
#include <Rendering/Window.hpp>

namespace atom
{
    CoreEngine::CoreEngine(unsigned int width, unsigned int height, Game* game) :
        game(game), window(new Window(width, height, game->GetName())),
        isRunning(false), renderer3D(window)
    {
        game->engine = this;
        game->root.engine = this;

        Time::Init();
        Input::Init();
        renderer3D.Init();
    }

    CoreEngine::~CoreEngine()
    {
        delete game;
        delete window;
    }

    void CoreEngine::Run()
    {
        isRunning = true;
        
        game->Start();

        while (isRunning)
        {
            window->Update();
            Time::Update();

            game->Update();
            game->Render(renderer3D);
            window->Render();

            isRunning = !window->IsClosed();
        }

        game->Stop();
    }
    
    void CoreEngine::Stop()
    {
        isRunning = false;
    }

    Window* CoreEngine::GetWindow() const
    {
        return window;
    }

    Renderer3D& CoreEngine::GetRenderer3D()
    {
        return renderer3D;
    }
    
    bool CoreEngine::IsRunning() const
    {
        return isRunning;
    }

    unsigned int CoreEngine::GetWidth() const
    {
        return window->GetWidth();
    }

    unsigned int CoreEngine::GetHeight() const
    {
        return window->GetHeight();
    }
}
