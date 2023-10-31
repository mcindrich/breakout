#include "SceneManager.h"

SceneManager::SceneManager()
{
}

void SceneManager::addScene(const std::string &name, IScene* scene)
{
	m_scenes[name] = std::unique_ptr<IScene>(scene);
}

void SceneManager::setCurrentScene(const std::string& name)
{
	m_currentScene = name;
}

std::unique_ptr<IScene>& SceneManager::getCurrentScene()
{
	return m_scenes[m_currentScene];
}
