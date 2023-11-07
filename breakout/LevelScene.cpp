#include "LevelScene.h"
#include "Level.h"
#include "Game.h"
#include "Paddle.h"
#include "Ball.h"
#include "ImpenetrableBrick.h"
#include "NormalBrick.h"
#include "HUDScene.h"

#include <sstream>
#include <iostream>

#include <tinyxml2.h>
using namespace tinyxml2;

LevelScene::LevelScene(Game* game, unsigned int level) : IScene(game)
{
	std::stringstream ss;

	ss << "./assets/levels/level-" << level << ".xml";

	auto level_path = ss.str();

	auto document = XMLDocument(true, tinyxml2::COLLAPSE_WHITESPACE);
	
	document.LoadFile(level_path.c_str());

	auto root_element = document.FirstChildElement();
	auto level_config = Level(root_element);

	// create game objects from the level configuration
	m_levelBackground = level_config.getBackgroundTexture();

	// get window size
	glm::ivec2 window_size;
	SDL_GetWindowSize(getGameRef()->getWindow(), &window_size.x, &window_size.y);

	// load textures
	m_texManager.loadTexture(game->getRenderer(), "./assets/textures/bricks/brick-01.png", "bricks/brick-01.png");
	m_texManager.loadTexture(game->getRenderer(), "./assets/textures/bricks/brick-02.png", "bricks/brick-02.png");
	m_texManager.loadTexture(game->getRenderer(), "./assets/textures/bricks/brick-03.png", "bricks/brick-03.png");
	m_texManager.loadTexture(game->getRenderer(), "./assets/textures/bricks/brick-04.png", "bricks/brick-04.png");
	m_texManager.loadTexture(game->getRenderer(), "./assets/textures/bg/background.png", "bg/background.png");
	m_texManager.loadTexture(game->getRenderer(), "./assets/textures/paddle.png", "paddle.png");
	m_texManager.loadTexture(game->getRenderer(), "./assets/textures/ball.png", "ball.png");

	// create game objects
	m_paddle = std::make_unique<Paddle>(m_texManager);
	m_ball = std::make_unique<Ball>(m_texManager);
	m_background = std::make_unique<Background>(m_texManager, m_levelBackground, window_size);

	// setup HUD part of the scene
	m_hudScene = std::make_unique<HUDScene>(getGameRef(), this);

	auto &bricks_layout = level_config.getBricksLayout();
	auto& brick_types = level_config.getBrickTypes();

	// use this position to calculate positions for each brick
	glm::vec2 brick_position(m_background->getPosition().x, m_background->getPosition().y + level_config.getRowSpacing());

	// use constant calculated size for each brick depending on a number of bricks and column spacing
	const auto bricks_row_count = level_config.getColumnCount();
	glm::vec2 brick_size = glm::vec2((m_background->getSize().x - (bricks_row_count + 1) * level_config.getColumnSpacing()) / (float)bricks_row_count, 15);

	std::cout << "Size: " << brick_size.x << " : " << brick_size.y << std::endl;

	// |- COL spacing -| |----| ... |----| |- COL spacing-|
	// |- ROW spacing -|
	// |- COL spacing -| |----| ... |----| |- COL spacing-|
	// NUM of col spacings = N_Bricks - 1 + 2 = N_Bricks + 1
	// Apply row spacing each time you enter a new row

	// generate bricks layout
	m_bricks.reserve(level_config.getRowCount());
	for (unsigned int i = 0; i < level_config.getRowCount(); i++) {
		m_bricks.push_back(std::vector<std::unique_ptr<Brick>>());
		brick_position.x = m_background->getPosition().x + (float)level_config.getColumnSpacing();
		for (unsigned int j = 0; j < level_config.getColumnCount(); j++) {
			auto& current_brick_sym = bricks_layout[i][j];

			if (current_brick_sym != '_') {
				auto& brick_type = brick_types[current_brick_sym];

				if (brick_type.isInfinite()) {
					// add impenetrable brick to the list
					m_bricks[i].push_back(std::make_unique<ImpenetrableBrick>(m_texManager, brick_type, brick_position, brick_size));
				}
				else {
					// add normal brick to the list
					m_bricks[i].push_back(std::make_unique<NormalBrick>(m_texManager, brick_type, brick_position, brick_size));
				}
			}
			brick_position.x += brick_size.x + level_config.getColumnSpacing();
		}
		brick_position.y += brick_size.y + level_config.getRowSpacing();
	}

	// initial count
	m_startTimer.restart();
	m_startCounter = 0;
}

void LevelScene::processEvents()
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

void LevelScene::update(float delta)
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_LEFT])
	{
		m_paddle->moveLeft(delta);
	}
	if (state[SDL_SCANCODE_RIGHT])
	{
		m_paddle->moveRight(delta);
	}
	m_hudScene->update(delta);
}

void LevelScene::render(SDL_Renderer* renderer)
{
	renderLevelBackground(renderer);
	renderLevelBricks(renderer);
	renderPaddle(renderer);
	renderBall(renderer);
	renderHUD(renderer);
}

void LevelScene::renderLevelBackground(SDL_Renderer* renderer)
{
	m_background->render(renderer);
}

void LevelScene::renderLevelBricks(SDL_Renderer* renderer)
{
	for (auto& i : m_bricks) {
		for (auto& j : i) {
			j->render(renderer);
		}
	}
}

void LevelScene::renderPaddle(SDL_Renderer* renderer)
{
	m_paddle->render(renderer);
}

void LevelScene::renderBall(SDL_Renderer* renderer)
{
	m_ball->render(renderer);
}

void LevelScene::renderHUD(SDL_Renderer* renderer)
{
	m_hudScene->render(renderer);
}
