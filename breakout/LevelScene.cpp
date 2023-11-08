#include "LevelScene.h"
#include "Game.h"
#include "Paddle.h"
#include "Ball.h"
#include "ImpenetrableBrick.h"
#include "NormalBrick.h"

// assets
#include "LevelConfigurationAsset.h"
#include "FontAsset.h"
#include "SFXAsset.h"
#include "ImageAsset.h"

#include <sstream>
#include <iostream>

LevelScene::LevelScene(Game& game, unsigned int level) : IScene(game), m_level(level), m_points(0), m_lives(3)
{
	loadLevelConfigurationAsset(level);
	loadBackgroundAsset();
	loadPaddleImageAsset();
	loadBallImageAsset();
	loadBrickImageAssets();
	loadBrickSFXAssets();
	loadFontAssets();
	createGameObjects();
	generateBricks();
	setupStartTimer();
	setupHUD();
}

void LevelScene::processEvents()
{
	SDL_Event event;

	// check for window close event
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			getGameRef().stopRunning();
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

	m_ball->updatePosition(delta);
}

void LevelScene::render(SDL_Renderer* renderer)
{
	renderLevelBackground(renderer);
	renderLevelBricks(renderer);
	renderBall(renderer);
	renderPaddle(renderer);
	renderHUD(renderer);
}

void LevelScene::loadLevelConfigurationAsset(unsigned int level)
{
	std::stringstream path_ss;
	path_ss << "./assets/levels/level-" << level << ".xml";
	auto level_path = path_ss.str();

	m_assetManager.loadAsset<LevelConfigurationAsset>(level_path, "LevelConfiguration");
}

void LevelScene::loadBackgroundAsset()
{
	std::stringstream path_ss;

	auto& level_config = m_assetManager.getAsset<LevelConfigurationAsset>("LevelConfiguration");

	// create game objects from the level configuration
	auto background_texture = level_config.getBackgroundTexture();

	path_ss << "./assets/textures/" << background_texture;

	auto background_path = path_ss.str();

	m_assetManager.loadAsset<ImageAsset>(background_path, background_texture);
	m_textureManager.createTextureFromImage(getGameRef().getRenderer(), m_assetManager.getAsset<ImageAsset>(background_texture), background_texture);
}

void LevelScene::loadBrickImageAssets()
{
	auto& level_config = m_assetManager.getAsset<LevelConfigurationAsset>("LevelConfiguration");

	for (auto &bt : level_config.getBrickTypes()) {
		std::stringstream path_ss;

		auto texture_name = bt.second.getBrickTextureName();

		path_ss << "./assets/textures/" << texture_name;

		auto texture_path = path_ss.str();

		m_assetManager.loadAsset<ImageAsset>(texture_path, texture_name);
		m_textureManager.createTextureFromImage(getGameRef().getRenderer(), m_assetManager.getAsset<ImageAsset>(texture_name), texture_name);
	}
}

void LevelScene::loadPaddleImageAsset()
{
	std::stringstream path_ss;

	auto& level_config = m_assetManager.getAsset<LevelConfigurationAsset>("LevelConfiguration");

	auto paddle_texture = level_config.getPaddleTexture();

	path_ss << "./assets/textures/" << paddle_texture;

	auto texture_path = path_ss.str();

	m_assetManager.loadAsset<ImageAsset>(texture_path, paddle_texture);
	m_textureManager.createTextureFromImage(getGameRef().getRenderer(), m_assetManager.getAsset<ImageAsset>(paddle_texture), paddle_texture);
}

void LevelScene::loadBallImageAsset()
{
	std::stringstream path_ss;

	auto& level_config = m_assetManager.getAsset<LevelConfigurationAsset>("LevelConfiguration");

	auto ball_texture = level_config.getBallTexture();

	path_ss << "./assets/textures/" << ball_texture;

	auto texture_path = path_ss.str();

	m_assetManager.loadAsset<ImageAsset>(texture_path, ball_texture);
	m_textureManager.createTextureFromImage(getGameRef().getRenderer(), m_assetManager.getAsset<ImageAsset>(ball_texture), ball_texture);
}

void LevelScene::loadBrickSFXAssets()
{
	auto& level_config = m_assetManager.getAsset<LevelConfigurationAsset>("LevelConfiguration");

	for (auto& bt : level_config.getBrickTypes()) {
		std::stringstream hit_path_ss;
		std::stringstream break_path_ss;

		auto hit_sfx_name = bt.second.getHitSoundName();
		auto break_sfx_name = bt.second.getBreakSoundName();

		hit_path_ss << "./assets/sfx/" << hit_sfx_name;
		break_path_ss << "./assets/sfx/" << break_sfx_name;

		m_assetManager.loadAsset<SFXAsset>(hit_path_ss.str(), hit_sfx_name);
		if (!bt.second.isInfinite()) {
			m_assetManager.loadAsset<SFXAsset>(break_path_ss.str(), break_sfx_name);
		}
	}
}

void LevelScene::loadFontAssets()
{
	m_assetManager.loadAsset<FontAsset>("./assets/fonts/Roboto-Regular.ttf", "HUDFont", 50);
}

void LevelScene::generateBricks()
{
	auto& level_config = m_assetManager.getAsset<LevelConfigurationAsset>("LevelConfiguration");

	auto& bricks_layout = level_config.getBricksLayout();
	auto& brick_types = level_config.getBrickTypes();

	// use this position to calculate positions for each brick
	glm::vec2 brick_position(m_background->getPosition().x, m_background->getPosition().y + level_config.getRowSpacing());

	// use constant calculated size for each brick depending on a number of bricks and column spacing
	const auto bricks_row_count = level_config.getColumnCount();
	glm::vec2 brick_size = glm::vec2((m_background->getSize().x - (bricks_row_count + 1) * level_config.getColumnSpacing()) / (float)bricks_row_count, 15);

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
					m_bricks[i].push_back(std::make_unique<ImpenetrableBrick>(m_textureManager, brick_type, brick_position, brick_size));
				}
				else {
					// add normal brick to the list
					m_bricks[i].push_back(std::make_unique<NormalBrick>(m_textureManager, brick_type, brick_position, brick_size));
				}
			}
			brick_position.x += brick_size.x + level_config.getColumnSpacing();
		}
		brick_position.y += brick_size.y + level_config.getRowSpacing();
	}
}

void LevelScene::createGameObjects()
{
	// get window size
	auto& level_config = m_assetManager.getAsset<LevelConfigurationAsset>("LevelConfiguration");

	auto &game_ref = getGameRef();
	auto renderer = game_ref.getRenderer();

	auto window_size = getWindowSize();

	// create game objects
	m_paddle = std::make_unique<Paddle>(m_textureManager, level_config.getPaddleTexture(), level_config.getPaddleSpeed());
	m_ball = std::make_unique<Ball>(m_textureManager, level_config.getBallTexture(), level_config.getBallSpeed());
	m_background = std::make_unique<Background>(m_textureManager, level_config.getBackgroundTexture(), window_size);
	m_hud = std::make_unique<HeadsUpDisplay>(m_assetManager, m_lives, m_points, m_level, getWindowSize());
}

void LevelScene::setupStartTimer()
{
	// initial count
	m_startTimer.restart();
	m_startCounter = 0;
}

void LevelScene::setupHUD()
{

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
	m_hud->render(renderer);
}

glm::ivec2 LevelScene::getWindowSize()
{
	glm::ivec2 window_size = glm::ivec2(0);
	SDL_GetWindowSize(getGameRef().getWindow(), &window_size.x, &window_size.y);

	return window_size;
}
