#include <Atom/Graphics/OpenGL.hpp>
#include <Atom/Debug/Debug.hpp>
#include <Atom/Engine.hpp>
#include <Atom/Graphics/Window.hpp>

namespace atom
{
	void WindowResize(GLFWwindow* window, int width, int height);
	void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void CursorPositionCallback(GLFWwindow* window, double x, double y);

	Window::Window(const std::string& title, int width, int height)
	{
		m_Title = title;
		m_Width = width;
		m_Height = height;

		memset(m_Keys, false, KEY_NUMBER);
		memset(m_KeyState, false, KEY_NUMBER);
		memset(m_KeyTyped, false, KEY_NUMBER);
		memset(m_MouseButtons, false, MOUSEBUTTON_NUMBER);
		memset(m_MouseState, false, MOUSEBUTTON_NUMBER);
		memset(m_MouseClicked, false, MOUSEBUTTON_NUMBER);

		Debug::Log("Creating the window...\n");

		if (!Init())
			glfwTerminate();
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Window::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::Update()
	{
		for (int i = 0; i < KEY_NUMBER; i++)
			m_KeyTyped[i] = m_Keys[i] && !m_KeyState[i];

		for (int i = 0; i < MOUSEBUTTON_NUMBER; i++)
			m_MouseClicked[i] = m_MouseButtons[i] && !m_MouseState[i];

		memcpy(m_KeyState, m_Keys, KEY_NUMBER);
		memcpy(m_MouseState, m_MouseButtons, MOUSEBUTTON_NUMBER);

		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void Window::SetTitle(const std::string& title)
	{
		glfwSetWindowTitle(m_Window, title.c_str());
		m_Title = title;

		Debug::Log("Window title set: " + title + "\n");
	}

	bool Window::Init()
	{
		if (!glfwInit())
		{
			Debug::Error("Failed to initialize GLFW\n");
			return false;
		}

		Debug::Log("GLFW initialized\n");

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);

		if (!m_Window)
		{
			glfwTerminate();
			Debug::Error("Failed to create the window!\n");
			return false;
		}

		Debug::Log("Window created\n");
		
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetFramebufferSizeCallback(m_Window, WindowResize);
		glfwSetKeyCallback(m_Window, KeyCallback);
		glfwSetMouseButtonCallback(m_Window, MouseButtonCallback);
		glfwSetCursorPosCallback(m_Window, CursorPositionCallback);
		glfwSwapInterval(0);

		if (glewInit() != GLEW_OK)
		{
			Debug::Error("Failed to initialize GLEW\n");
			return false;
		}

		Debug::Log("GLEW initialized, using the OpenGL Rendering API\n");
		Debug::Log("OpenGL Version: " + std::string((const char*)glGetString(GL_VERSION)) + '\n');

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return true;
	}

	bool Window::Closed() const
	{
		return glfwWindowShouldClose(m_Window);
	}

	bool Window::IsKeyPressed(unsigned int keyCode) const
	{
		if (keyCode >= KEY_NUMBER)
			return false;

		return m_Keys[keyCode];
	}

	bool Window::IsKeyTyped(unsigned int keyCode) const
	{
		if (keyCode >= KEY_NUMBER)
			return false;

		return m_KeyTyped[keyCode];
	}

	bool Window::IsMouseButtonPressed(unsigned int button) const
	{
		if (button >= MOUSEBUTTON_NUMBER)
			return false;

		return m_MouseButtons[button];
	}

	bool Window::IsMouseButtonClicked(unsigned int button) const
	{
		if (button >= MOUSEBUTTON_NUMBER)
			return false;

		return m_MouseClicked[button];
	}

	void WindowResize(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
		
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_Width = width;
		win->m_Height = height;

		Debug::Log("Window resized: " + std::to_string(width) + ", " + std::to_string(height) + "\n");
	}

	void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_Keys[key] = action != GLFW_RELEASE;
	}

	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_MouseButtons[button] = action != GLFW_RELEASE;
	}

	void CursorPositionCallback(GLFWwindow* window, double x, double y)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_MouseX = (float)x;
		win->m_MouseY = (float)y;
	}
}
