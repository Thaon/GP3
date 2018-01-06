#pragma once

#include "Common.h"
#include "Scene.h"

/***
	The Scenemanager class offers static functionality to store, access and operate on Scenes
*/

class SceneManager
{
public:
	static void CreateScene(std::string sceneName);

	static Scene* GetScene(std::string sceneName);
	static Scene* GetScene(int sceneIndex);

	static void SetActiveScene(std::string sceneName);
	static void SetActiveScene(int sceneIndex);

	static Scene* GetActiveScene();


private:
	static std::vector<Scene*> m_scenes;
	static Scene* m_activeScene;
};

