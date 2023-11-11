#include "SceneManager.h"

SceneManager::SceneManager()
{
}

void SceneManager::setCurrentScene(const std::string& name)
{
	m_currentScene = name;
}

std::unique_ptr<Scene>& SceneManager::getCurrentScene()
{
	return m_scenes[m_currentScene];
}
