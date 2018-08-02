#include <Atom/Debug/Debug.hpp>
#include <Atom/Scenes/Scene.hpp>
#include <Atom/Scenes/SceneManager.hpp>

namespace atom
{
	unsigned int SceneManager::m_CurrentIndex = 0;
	Scene* SceneManager::m_CurrentScene = nullptr;
	std::vector<SceneData> SceneManager::m_Scenes;

	void SceneManager::Init()
	{
		Debug::Log("Scene Manager initialized\n");
	}

	void SceneManager::Clean()
	{
		if (m_CurrentScene != nullptr)
			delete m_CurrentScene;

		Debug::Log("Scene Manager cleaned\n");
	}

	void SceneManager::Update()
	{
		m_CurrentScene->Update();
	}

	void SceneManager::Render()
	{
		m_CurrentScene->Render();
	}

	void SceneManager::LoadScene(const std::string& name)
	{
		for (SceneData& i : m_Scenes)
		{
			if (i.name == name)
			{
				LoadScene(i.buildIndex);
				return;
			}
		}

		Debug::Error("Scene" + name + "not found!\n");
	}

	void SceneManager::LoadScene(unsigned int buildIndex)
	{
		if (buildIndex >= m_Scenes.size())
		{
			Debug::Error("Build index too big!\n");
			return;
		}

		if (m_CurrentScene != nullptr)
		{
			Debug::Log("Scene " + m_CurrentScene->GetName() + " deleted\n");

			delete m_CurrentScene;
			m_CurrentScene = nullptr;
		}

		m_CurrentScene = m_Scenes[buildIndex].instantiate();
		m_CurrentScene->m_SceneData = &m_Scenes[buildIndex];
		
		Debug::Log("Scene " + m_CurrentScene->GetName() + " loaded\n");
	}

	const SceneData& SceneManager::Get(const std::string& name)
	{
		for (SceneData& i : m_Scenes)
		{
			if (i.name == name)
				return i;
		}

		return m_Scenes[0];
	}

	const SceneData& SceneManager::Get(unsigned int buildIndex)
	{
		return m_Scenes[buildIndex];
	}
}
