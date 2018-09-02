#include <Atom/Engine.hpp>
#include <Atom/Input/Input.hpp>

namespace Atom
{
	namespace Input
	{
		bool IsKeyPressed(unsigned int keyCode)
		{
			return Engine::m_Window->IsKeyPressed(keyCode);
		}

		bool IsKeyTyped(unsigned int keyCode)
		{
			return Engine::m_Window->IsKeyTyped(keyCode);
		}

		bool IsMouseButtonPressed(unsigned int button)
		{
			return Engine::m_Window->IsMouseButtonPressed(button);
		}

		bool IsMouseButtonClicked(unsigned int button)
		{
			return Engine::m_Window->IsMouseButtonClicked(button);
		}
	}
}
