#include <Atom/Debug/Debug.hpp>
#include <Atom/Scenes/Scene.hpp>

namespace Atom
{
	namespace SceneManager
	{
		Scene* currentScene = nullptr;

		void Clean()
		{
			if (currentScene != nullptr)
				delete currentScene;

			Debug::Log("[Atom]: Scene Manager cleaned\n");
		}

		void Update()
		{
			currentScene->Update();
		}

		void Render()
		{
			currentScene->Render();
		}

		const Scene* GetCurrentScene()
		{
			return currentScene;
		}
	}
}
