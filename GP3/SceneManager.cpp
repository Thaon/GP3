#include "SceneManager.h"

std::vector<Scene*> SceneManager::m_scenes = std::vector<Scene*>();
Scene* SceneManager::m_activeScene = nullptr;

void SceneManager::CreateScene(std::string sceneName)
{
	m_scenes.push_back(new Scene(sceneName));
	m_activeScene = GetScene(sceneName);
}

Scene* SceneManager::GetScene(std::string sceneName)
{
	for (auto scene : m_scenes)
	{
		if (scene->GetName() == sceneName)
			return scene;
	}
	std::cout << "could not find scene named: " << sceneName << std::endl;
	return nullptr;
}

Scene* SceneManager::GetScene(int sceneIndex)
{
	if (m_scenes.size() > sceneIndex)
		return m_scenes.at(sceneIndex);
	else
	{
		std::cout << "not enough scenes in the scene manager!" << std::endl;
		return nullptr;
	}
}

void SceneManager::SetActiveScene(std::string sceneName)
{
	m_activeScene = GetScene(sceneName);
}

void SceneManager::SetActiveScene(int sceneIndex)
{
	if (m_scenes.size() > sceneIndex)
		m_activeScene = m_scenes.at(sceneIndex);
	else
	{
		std::cout << "not enough scenes in the scene manager!" << std::endl;
	}
}

Scene* SceneManager::GetActiveScene()
{
	return m_activeScene;
}
