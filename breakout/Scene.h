#pragma once

#include <SDL_render.h>

class Game;

class Scene
{
public:
	Scene(Game& game);

	virtual void processEvents() = 0;

	virtual void update(float delta) = 0;

	virtual void render(SDL_Renderer *renderer) = 0;

	Game& getGameRef();

private:
	Game& m_game;
};

