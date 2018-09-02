#pragma once

#include <Atom/Input/Keyboard.hpp>
#include <Atom/Input/Joystick.hpp>
#include <Atom/Input/Mouse.hpp>
#include <Atom/Graphics/Window.hpp>

/*
 *	TO DO: Put the keys, joystick
 *	and mouse buttons into enums
 */

namespace Atom
{
	namespace Input
	{
		bool IsKeyPressed(unsigned int keyCode);
		bool IsKeyTyped(unsigned int keyCode);
		bool IsMouseButtonPressed(unsigned int button);
		bool IsMouseButtonClicked(unsigned int button);
	}
}
