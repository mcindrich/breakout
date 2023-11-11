#pragma once

#include <memory>
#include <map>
#include <vector>

#include <SDL.h>
#include <imgui.h>

#include "SceneManager.h"
#include "Timer.h"

class Game
{
public:
	Game(SDL_Window *window, SDL_Renderer *renderer);

	void run();

	void stopRunning();

	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();

	void setCurrentScene(const std::string& scene_name);

	SceneManager &getSceneManager();

	~Game();

private:
	SceneManager m_sceneManager;
	bool m_running;

	// SDL2 stuff
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;

	Timer m_deltaTimer;
};