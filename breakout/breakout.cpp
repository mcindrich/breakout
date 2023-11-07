#include <iostream>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

#include <SDL_image.h>
#include <SDL.h>

#include "Game.h"

// SDL2main fix
#undef main

int main()
{
	// init SDL
	int error = 0;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::printf("Unable to initialize SDL\n");
		return -1;
	}

	//Initialize PNG loading
	int flags = IMG_INIT_PNG;
	if (!(IMG_Init(flags) & flags))
	{
		std::printf("SDL_image init error: %s\n", IMG_GetError());
		return -2;
	}

	window = SDL_CreateWindow("breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, 0);
	if (!window) {
		std::printf("Unable to create a window handle\n");
		return -3;
	}

	// create a renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::printf("Unable to create a renderer\n");
		return -4;
	}

	// init ImGui
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer2_Init(renderer);

	try {
		Game game(window, renderer);

		game.run();
	}
	catch (const std::runtime_error& ex) {
		std::printf("Error occured: %s\n", ex.what());
		error = -5;
	}

	// close SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return error;
}