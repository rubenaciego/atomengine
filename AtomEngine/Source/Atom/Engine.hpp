#pragma once

#include <Atom/Input/Input.hpp>

namespace Atom
{
	class Window;

	class Engine
	{
	public:
		static void Init(const std::string& windowTitle, int width, int height);
		static void Clean();
		static void Update();

		static bool Running();

	private:
		Engine() {}
		static Window* m_Window;

		friend class Window;
		friend class Scene2D;
		friend class Light2D;
		friend class Renderer2D;

		friend bool Input::IsKeyPressed(unsigned int keyCode);
		friend bool Input::IsKeyTyped(unsigned int keyCode);
		friend bool Input::IsMouseButtonPressed(unsigned int button);
		friend bool Input::IsMouseButtonClicked(unsigned int button);
	};
}
