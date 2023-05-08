#pragma once

#include <Rendering/Renderer3D.hpp>

namespace atom
{
    class Game;
    class Window;

    class CoreEngine
    {
    public:
        CoreEngine(unsigned int width, unsigned int height, Game* game);
        ~CoreEngine();

        void Run();
        void Stop();

        Window* GetWindow() const;
        Renderer3D& GetRenderer3D();
        bool IsRunning() const;
        unsigned int GetWidth() const;
        unsigned int GetHeight() const;

    private:
        Game* game;
        Window* window;
        bool isRunning;

        Renderer3D renderer3D;
    };
}
