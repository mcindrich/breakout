#pragma once

#include <map>
#include <vector>
#include <string>
#include <memory>

#include "IScene.h"

class SceneManager
{
public:
	SceneManager();

	template <typename SceneType>
	void addScene(const std::string &name, Game& game);

	void addScene(const std::string& name, IScene* scene);

	template<typename SceneType>
	SceneType& getScene(const std::string& name);

	void setCurrentScene(const std::string& name);

	std::unique_ptr<IScene> &getCurrentScene();


private:
	std::map<std::string, std::unique_ptr<IScene>> m_scenes;
	std::string m_currentScene;
};

template<typename SceneType>
inline void SceneManager::addScene(const std::string& name, Game& game)
{
	auto scene = std::make_unique<SceneType>(game);

	m_scenes[name] = std::move(scene);
}

template<typename SceneType>
inline SceneType& SceneManager::getScene(const std::string& name)
{
	auto scene_ptr = m_scenes[name].get();

	return *dynamic_cast<SceneType*>(scene_ptr);
}
