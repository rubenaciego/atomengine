#pragma once

#include <string>
#include <vector>
#include <functional>

namespace atom
{
	class Scene;

	struct SceneData
	{
		unsigned int buildIndex;
		std::string name;
		std::function<Scene*()> instantiate;
	};

	class SceneManager
	{
	public:
		static void Init();
		static void Clean();
		static void Update();
		static void Render();
		static const SceneData& Get(const std::string &name);
		static const SceneData& Get(unsigned int buildIndex);
		static void LoadScene(const std::string& name);
		static void LoadScene(unsigned int buildIndex);
		
		template<typename T> static void Add(const std::string& sceneName)
		{
			m_Scenes.push_back(SceneData { m_CurrentIndex++, sceneName, [](){
				return (Scene*)(new T());
			}});
		}

	private:
		SceneManager() {}
		static unsigned int m_CurrentIndex;
		static Scene* m_CurrentScene;
		static std::vector<SceneData> m_Scenes;

		friend class Scene;
	};
}
