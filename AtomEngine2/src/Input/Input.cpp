#include "Input.hpp"
#include <Debug/Log.hpp>
#include <SDL2/SDL.h>

namespace atom
{
    uint8_t Input::keyDownState[Key::NUM_SCANCODES] = { 0 };
    uint8_t Input::keyUpState[Key::NUM_SCANCODES] = { 0 };
    uint8_t Input::mouseDownState[MouseButton::X2] = { 0 };
    uint8_t Input::mouseUpState[MouseButton::X2] = { 0 };
    int Input::mouseX = 0;
    int Input::mouseY = 0;
    int Input::mouseVelX = 0;
    int Input::mouseVelY = 0;

    void Input::Init()
    {
        ATOM_CORE_LOG("[Atom]: Input subsystem initialized\n");
    }

    bool Input::GetKey(int keyCode)
    {
        return SDL_GetKeyboardState(nullptr)[keyCode];
    }

    bool Input::GetKeyDown(int keyCode)
    {
        if (keyDownState[keyCode])
        {
            keyDownState[keyCode] = false;
            return true;
        }
        
        return false;
    }

    bool Input::GetKeyUp(int keyCode)
    {
        if (keyUpState[keyCode])
        {
            keyUpState[keyCode] = false;
            return true;
        }
        
        return false;
    }

    int Input::GetMouseX()
    {
        SDL_GetMouseState(&mouseX, &mouseY);
        return mouseX;
    }

    int Input::GetMouseY()
    {
        SDL_GetMouseState(&mouseX, &mouseY);
        return mouseY;
    }

    Vector2 Input::GetMousePos()
    {
        SDL_GetMouseState(&mouseX, &mouseY);
        return { (float)mouseX, (float)mouseY };
    }

    int Input::GetMouseVelX()
    {
        float ret = mouseVelX;
        mouseVelX = 0;

        return ret;
    }

    int Input::GetMouseVelY()
    {
        float ret = mouseVelY;
        mouseVelY = 0;

        return ret;
    }

    Vector2 Input::GetMouseVel()
    {
        Vector2 ret((float)mouseVelX, (float)mouseVelY);
        
        mouseVelX = 0;
        mouseVelY = 0;

        return ret;
    }

    bool Input::GetMouseButton(int button)
    {
        return SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(button);
    }

    bool Input::GetMouseButtonDown(int button)
    {
        if (mouseDownState[button])
        {
            mouseDownState[button] = false;
            return true;
        }
        
        return false;
    }

    bool Input::GetMouseButtonUp(int button)
    {
        if (mouseUpState[button])
        {
            mouseUpState[button] = false;
            return true;
        }
        
        return false;
    }

    void Input::LockCursor(bool lock)
    {
        SDL_SetRelativeMouseMode((SDL_bool)lock);
    }
}
