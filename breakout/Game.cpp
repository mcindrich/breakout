#include "Game.h"
#include "GameScene.h"
#include "LevelScene.h"

#include <stdexcept>

Game::Game(SDL_Window* window) : m_running(false), m_window(window)
{
	// create a renderer
	m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!m_renderer) {
		throw std::runtime_error("Unable to create a hardware accelerated renderer");
	}
	
	// initialize scenes
	m_sceneManager.addScene("LevelScene", new LevelScene(this, 0));

	// setup current scene
	m_sceneManager.setCurrentScene("LevelScene");
}

void Game::run()
{
	m_running = true;

	while (m_running) {
		// get the current scene
		auto& current_scene = m_sceneManager.getCurrentScene();

		// process events
		current_scene->processEvents();

		// call update
		current_scene->update(m_deltaTimer.restart());

		// call render
		SDL_SetRenderDrawColor(m_renderer, 35, 35, 35, 255);
		SDL_RenderClear(m_renderer);

		// render scene to the renderer
		current_scene->render(m_renderer);

		// present the scene
		SDL_RenderPresent(m_renderer);
	}
}

void Game::stopRunning()
{
	m_running = false;
}

SDL_Window* Game::getWindow()
{
	return m_window;
}

SDL_Renderer* Game::getRenderer()
{
	return m_renderer;
}
