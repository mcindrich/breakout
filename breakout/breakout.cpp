#include <iostream>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "Game.h"

#include <cstdlib>

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
		return -1;
	}

	// Initialize Mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::printf("SDL_mixer init error: %s\n", Mix_GetError());
		return -1;
	}

	if (TTF_Init() == -1) {
		std::printf("SDL_ttf init error: %s\n", TTF_GetError());
		return -1;
	}

	// init rand seed
	std::srand(std::time(NULL));

	window = SDL_CreateWindow("breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, 0);
	if (!window) {
		std::printf("Unable to create a window handle\n");
		return -1;
	}

	// create a renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::printf("Unable to create a renderer\n");
		return -1;
	}

	// init ImGui
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

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
		error = -1;
	}

	// close SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	// Quit all SDL stuff
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return error;
}