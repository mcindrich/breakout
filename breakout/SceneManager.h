#pragma once

#include <map>
#include <vector>
#include <string>
#include <memory>

#include "Scene.h"

class SceneManager
{
public:
	SceneManager();

	template <typename SceneType, typename... Args>
	void addScene(const std::string &name, Game& game, Args&&... args);

	template<typename SceneType>
	SceneType& getScene(const std::string& name);

	void setCurrentScene(const std::string& name);

	std::unique_ptr<Scene> &getCurrentScene();


private:
	std::map<std::string, std::unique_ptr<Scene>> m_scenes;
	std::string m_currentScene;
};

template<typename SceneType, typename ...Args>
inline void SceneManager::addScene(const std::string& name, Game& game, Args && ...args)
{
	auto scene = std::make_unique<SceneType>(game, std::forward<Args>(args)...);

	m_scenes[name] = std::move(scene);
}

template<typename SceneType>
inline SceneType& SceneManager::getScene(const std::string& name)
{
	auto scene_ptr = m_scenes[name].get();

	return *dynamic_cast<SceneType*>(scene_ptr);
}
