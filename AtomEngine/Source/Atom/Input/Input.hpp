#pragma once

#include <Atom/Input/Keyboard.hpp>
#include <Atom/Input/Joystick.hpp>
#include <Atom/Input/Mouse.hpp>
#include <Atom/Graphics/Window.hpp>
#include <Atom/Engine.hpp>

namespace atom
{
	class Input
	{
	public:
		inline static bool IsKeyPressed(unsigned int keyCode) { return Engine::m_Window->IsKeyPressed(keyCode); }
		inline static bool IsKeyTyped(unsigned int keyCode) { return Engine::m_Window->IsKeyTyped(keyCode); }
		inline static bool IsMouseButtonPressed(unsigned int button) { return Engine::m_Window->IsMouseButtonPressed(button); }
		inline static bool IsMouseButtonClicked(unsigned int button) { return Engine::m_Window->IsMouseButtonClicked(button); }

	private:
		Input() {}
	};
}
