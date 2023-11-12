#include "Game.h"
#include "LevelScene.h"
#include "MainMenuScene.h"

#include <stdexcept>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

Game::Game(SDL_Window* window, SDL_Renderer *renderer) : m_running(false), m_window(window), m_renderer(renderer)
{
	// initialize scenes
	m_sceneManager.addScene<MainMenuScene>("MainMenuScene", *this);

	// setup current scene
	m_sceneManager.setCurrentScene("MainMenuScene");
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

void Game::setCurrentScene(const std::string& scene_name)
{
	m_sceneManager.setCurrentScene(scene_name);
}

SceneManager& Game::getSceneManager()
{
	return m_sceneManager;
}

Game::~Game()
{
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}
