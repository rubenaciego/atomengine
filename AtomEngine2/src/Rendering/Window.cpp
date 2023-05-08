#include "Window.hpp"
#include <Debug/Log.hpp>
#include <Input/Input.hpp>
#include <Rendering/OpenGL.hpp>

namespace atom
{
    Window::Window(int w, int h, const std::string& title)
    {
        name = title;
        width = w;
        height = h;
        closed = false;

        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            ATOM_CORE_ERROR("[Atom]: Error initializing SDL: %s\n", SDL_GetError());
            return;
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

        if (window == nullptr)
        {
            ATOM_CORE_ERROR("[Atom]: Error creating the window: %s\n", SDL_GetError());
            return;
        }

        context = SDL_GL_CreateContext(window);
        SDL_GL_SetSwapInterval(1);

        if (glewInit() != GLEW_OK)
            ATOM_CORE_ERROR("[Atom]: Error initializing GLEW\n");
    }

    Window::~Window()
    {
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void Window::SetFullscreen(bool s) const
    {
        if (s)
        {
            SDL_DisplayMode dm;
            SDL_GetCurrentDisplayMode(0, &dm);
            SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
            GLCall(glViewport(0, 0, dm.w, dm.h));
        }
        else
        {
            SDL_SetWindowFullscreen(window, 0);
            GLCall(glViewport(0, 0, width, height));
        }
    }

    void Window::Update()
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    closed = true;
                break;

                case SDL_KEYDOWN:
                    Input::keyDownState[event.key.keysym.scancode] = true;
                break;

                case SDL_KEYUP:
                    Input::keyUpState[event.key.keysym.scancode] = true;
                break;

                case SDL_MOUSEBUTTONDOWN:
                    Input::mouseDownState[event.button.button] = true;
                break;

                case SDL_MOUSEBUTTONUP:
                    Input::mouseUpState[event.button.button] = true;
                break;

                case SDL_MOUSEMOTION:
                    Input::mouseVelX = event.motion.xrel;
                    Input::mouseVelY = event.motion.yrel;
                break;

                case SDL_WINDOWEVENT:
                    SDL_GetWindowSize(window, (int*)&width, (int*)&height);
                    GLCall(glViewport(0, 0, (int)width, (int)height));
                break;
            }
        }
    }

    void Window::Render()
    {
        SDL_GL_SwapWindow(window);
    }

    void Window::BindAsRenderTarget() const
    {
       GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
       GLCall(glViewport(0, 0, (int)width, (int)height));
    }

    bool Window::IsClosed() const
    {
        return closed;
    }

    unsigned int Window::GetWidth() const
    {
        return width;
    }
    
    unsigned int Window::GetHeight() const
    {
        return height;
    }
}
