#pragma once

#include <string>

struct GLFWwindow;

namespace atom
{
	class Window
	{
		#define KEY_NUMBER 120
		#define MOUSEBUTTON_NUMBER 11

	private:
		GLFWwindow* m_Window;
		std::string m_Title;
		int m_Width;
		int m_Height;
		float m_MouseX;
		float m_MouseY;

		bool m_Keys[KEY_NUMBER];
		bool m_KeyState[KEY_NUMBER];
		bool m_KeyTyped[KEY_NUMBER];
		bool m_MouseButtons[MOUSEBUTTON_NUMBER];
		bool m_MouseState[MOUSEBUTTON_NUMBER];
		bool m_MouseClicked[MOUSEBUTTON_NUMBER];

		bool Init();

		friend void WindowResize(GLFWwindow* window, int width, int height);
		friend void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
		friend void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		friend void CursorPositionCallback(GLFWwindow* window, double x, double y);

	public:
		Window(const std::string& title, int width, int height);
		~Window();

		bool Closed() const;
		void Clear() const;
		void Update();
		void SetTitle(const std::string& title);

		inline float GetMouseX() const { return m_MouseX; }
		inline float GetMouseY() const { return m_MouseY; }
		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }
		inline const std::string& GetTitle() const { return m_Title; }

		bool IsKeyPressed(unsigned int keyCode) const;
		bool IsKeyTyped(unsigned int keyCode) const;
		bool IsMouseButtonPressed(unsigned int button) const;
		bool IsMouseButtonClicked(unsigned int button) const;
	};
}
