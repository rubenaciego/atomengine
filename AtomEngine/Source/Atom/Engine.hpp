#pragma once

namespace atom
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
		friend class Input;
	};
}
