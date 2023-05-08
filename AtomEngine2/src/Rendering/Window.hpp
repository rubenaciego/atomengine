#pragma once

#include <SDL2/SDL.h>
#include <string>

namespace atom
{
    class Window
    {
    private:
        std::string name;
        unsigned int width, height;
        bool closed;

        SDL_Window* window;
        SDL_Event event;
        SDL_GLContext context;

    public:
        Window(int w, int h, const std::string& title);
        virtual ~Window();

        void SetFullscreen(bool s) const;
        void Update();
        void Render();
        void BindAsRenderTarget() const;
        bool IsClosed() const;
        unsigned int GetWidth() const;
        unsigned int GetHeight() const;
    };
}
