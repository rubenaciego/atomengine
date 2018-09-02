#pragma once

#include <Atom/Scenes/Scene.hpp>

namespace Atom
{
	namespace SceneManager
	{
		extern Scene* currentScene;

		template<typename T> void LoadScene()
		{
			if (currentScene != nullptr)
				delete currentScene;

			currentScene = (Scene*)new T();

			Debug::Log("[Atom]: New scene loaded\n");
		}

		void Update();
		void Render();
		void Clean();
		const Scene* GetCurrentScene();
	}
}
