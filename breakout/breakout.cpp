#include <iostream>
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

	try {
		Game game(window);

		game.run();
	}
	catch (const std::runtime_error& ex) {
		std::printf("Error occured: %s\n", ex.what());
		error = -4;
	}

	// close SDL
	SDL_DestroyWindow(window);
	SDL_Quit();

	return error;
}