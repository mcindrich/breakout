#include "GameScene.h"
#include "Game.h"
#include "Level.h"

#include <stdexcept>
#include <iostream>

#include <SDL_events.h>
#include <SDL_image.h>

GameScene::GameScene(Game *game) : IScene(game), m_levelDocument(true, tinyxml2::COLLAPSE_WHITESPACE)
{
	// start with level 0
	m_levelDocument.LoadFile("./assets/levels/level-0.xml");

	auto root_element = m_levelDocument.FirstChildElement();

	m_level = new Level(root_element);

	m_texManager.loadTexture(game->getRenderer(), "./assets/textures/bricks/brick-01.png", "bricks/brick-01.png");
	m_texManager.loadTexture(game->getRenderer(), "./assets/textures/bricks/brick-02.png", "bricks/brick-02.png");
	m_texManager.loadTexture(game->getRenderer(), "./assets/textures/bricks/brick-03.png", "bricks/brick-03.png");
	m_texManager.loadTexture(game->getRenderer(), "./assets/textures/bricks/brick-04.png", "bricks/brick-04.png");
	m_texManager.loadTexture(game->getRenderer(), "./assets/textures/bg/background.png", "bg/background.png");
}

void GameScene::processEvents()
{
	SDL_Event event;

	// check for window close event
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			getGameRef()->stopRunning();
			break;
		}
	}
}

void GameScene::update(float delta)
{
}

void GameScene::render(SDL_Renderer *renderer)
{
	renderLevelBackground(renderer);
	renderLevelBricks(renderer);
	renderPaddle(renderer);
	renderBall(renderer);
}

void GameScene::renderLevelBackground(SDL_Renderer* renderer)
{
	int width, height;
	SDL_Rect bg_rect;

	SDL_GetWindowSize(getGameRef()->getWindow(), &width, &height);

	bg_rect = {0, 0, width, height};

	auto& texture_ptr = m_texManager.getTexture(m_level->getBackgroundTexture());

	SDL_RenderCopy(renderer, texture_ptr.get(), NULL, &bg_rect);
}

void GameScene::renderLevelBricks(SDL_Renderer* renderer)
{
	auto& bricks_layout = m_level->getBricksLayout();
	auto& brick_types = m_level->getBrickTypes();

	int x, y = 0;
	const auto BRICK_WIDTH = 40;
	const auto BRICK_HEIGHT = 15;

	for (unsigned i = 0; i < m_level->getRowCount(); i++) {
		x = 2;
		for (unsigned j = 0; j < m_level->getColumnCount(); j++) {
			auto current_brick = bricks_layout[i][j];

			if (current_brick != '_') {
				auto brick_type = brick_types.at(current_brick);
				auto texture_name = brick_type.getBrickTextureName();
				auto& texture = m_texManager.getTexture(texture_name);

				SDL_Rect texture_rect = { x, y, BRICK_WIDTH, BRICK_HEIGHT, };


				SDL_RenderCopy(renderer, texture.get(), NULL, &texture_rect);
			}
			x += BRICK_WIDTH + 2;
		}
		y += BRICK_HEIGHT * 2;
	}
}

void GameScene::renderPaddle(SDL_Renderer* renderer)
{
}

void GameScene::renderBall(SDL_Renderer* renderer)
{
}
