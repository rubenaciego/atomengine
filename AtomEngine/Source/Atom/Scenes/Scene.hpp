#pragma once

#include <string>
#include "SceneManager.hpp"

namespace atom
{
	class Scene
	{
	private:
		SceneData* m_SceneData;

	public:
		Scene() {};
		virtual ~Scene() {};
		virtual void Update() {};
		virtual void Render() {}

		inline unsigned int GetBuildIndex() const { return m_SceneData->buildIndex; }
		inline const std::string& GetName() const { return m_SceneData->name; }
		
		friend class SceneManager;
	};
}
