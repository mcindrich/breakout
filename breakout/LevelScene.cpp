#include "LevelScene.h"
#include "Game.h"

// common
#include "Common.h"

// objects
#include "Paddle.h"
#include "Ball.h"
#include "ImpenetrableBrick.h"
#include "NormalBrick.h"

// assets
#include "LevelConfigurationAsset.h"
#include "FontAsset.h"
#include "SFXAsset.h"
#include "TextureAsset.h"

// collision
#include "AABBCollisionDetector.h"

#include <sstream>
#include <iostream>

// should be loaded from number of files in directory
constexpr auto MAX_LEVEL = 3;

LevelScene::LevelScene(Game& game, unsigned int level) : Scene(game), m_level(level), m_points(0), m_lives(3), m_state(LevelState::Starting)
{
	// load all assets
	loadLevelConfigurationAsset(level);
	loadBackgroundAsset();
	loadPaddleTextureAsset();
	loadBallTextureAsset();
	loadBrickTextureAssets();
	loadBrickSFXAssets();
	loadFontAssets();

	// create all objects by giving them the ref to needed assets
	createGameObjects();

	// setup all text data
	setupRoundStartText();
	setupLevelFailedText();
	setupLevelPassedText();
	setupLastLevelPassedText();

	// setup invisible wall objects used for wall collision detection
	setupWallPositionedObjects();
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
		case SDL_KEYDOWN:
			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
				// start the game if not already started
				switch (m_state) {
				case LevelState::Starting:
					m_state = LevelState::Playing;
					break;
				case LevelState::LevelFailed:
					resetLevel();
					break;
				case LevelState::Finished:
				case LevelState::FinishedLastLevel:
					advanceToNextLevel();
					break;
				default:
					break;
				}
			}
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
	if (state[SDL_SCANCODE_UP])
	{
		m_ball->setDirection(glm::vec2(0, -1));
	}
	if (state[SDL_SCANCODE_DOWN])
	{
		m_ball->setDirection(glm::vec2(0, 1));
	}

	if (m_state == LevelState::Playing) {
		m_ball->updatePosition(delta);

		// check for collisions
		checkCollisions();
	}
}

void LevelScene::render(SDL_Renderer* renderer)
{
	renderLevelBackground(renderer);
	renderLevelBricks(renderer);
	renderBall(renderer);
	renderPaddle(renderer);
	renderHUD(renderer);
	renderRoundStartText(renderer);
	renderLevelFailedText(renderer);
	renderLevelPassedText(renderer);
	renderLastLevelFinishedText(renderer);
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

	m_assetManager.loadAsset<TextureAsset>(background_path, background_texture, getGameRef().getRenderer());
}

void LevelScene::loadBrickTextureAssets()
{
	auto& level_config = m_assetManager.getAsset<LevelConfigurationAsset>("LevelConfiguration");

	for (auto &bt : level_config.getBrickTypes()) {
		std::stringstream path_ss;

		auto texture_name = bt.second.getBrickTextureName();

		path_ss << "./assets/textures/" << texture_name;

		auto texture_path = path_ss.str();

		m_assetManager.loadAsset<TextureAsset>(texture_path, texture_name, getGameRef().getRenderer());
	}
}

void LevelScene::loadPaddleTextureAsset()
{
	std::stringstream path_ss;

	auto& level_config = m_assetManager.getAsset<LevelConfigurationAsset>("LevelConfiguration");

	auto paddle_texture = level_config.getPaddleTexture();

	path_ss << "./assets/textures/" << paddle_texture;

	auto texture_path = path_ss.str();

	m_assetManager.loadAsset<TextureAsset>(texture_path, paddle_texture, getGameRef().getRenderer());
}

void LevelScene::loadBallTextureAsset()
{
	std::stringstream path_ss;

	auto& level_config = m_assetManager.getAsset<LevelConfigurationAsset>("LevelConfiguration");

	auto ball_texture = level_config.getBallTexture();

	path_ss << "./assets/textures/" << ball_texture;

	auto texture_path = path_ss.str();

	m_assetManager.loadAsset<TextureAsset>(texture_path, ball_texture, getGameRef().getRenderer());
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
	m_assetManager.loadAsset<FontAsset>("./assets/fonts/Roboto-Bold.ttf", "HUDFont", 100);
	m_assetManager.loadAsset<FontAsset>("./assets/fonts/ARCADECLASSIC.ttf", "TextFont", 100);
}

void LevelScene::generateBricks()
{
	auto& level_config = m_assetManager.getAsset<LevelConfigurationAsset>("LevelConfiguration");

	auto& bricks_layout = level_config.getBricksLayout();
	auto& brick_types = level_config.getBrickTypes();

	// use this position to calculate positions for each brick
	glm::vec2 brick_position(m_background->getTopLeftPosition().x, m_background->getTopLeftPosition().y + level_config.getRowSpacing());

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
		brick_position.x = m_background->getTopLeftPosition().x + (float)level_config.getColumnSpacing();
		for (unsigned int j = 0; j < level_config.getColumnCount(); j++) {
			auto& current_brick_sym = bricks_layout[i][j];

			if (current_brick_sym != '_') {
				auto& brick_type = brick_types[current_brick_sym];

				auto& brick_texture = m_assetManager.getAsset<TextureAsset>(brick_type.getBrickTextureName());
				auto& brick_hit_sound = m_assetManager.getAsset<SFXAsset>(brick_type.getHitSoundName());

				if (brick_type.isInfinite()) {
					// add impenetrable brick to the list
					m_bricks.push_back(std::make_unique<ImpenetrableBrick>(brick_texture, brick_hit_sound, brick_type, brick_position + brick_size / 2.0f, brick_size));
				}
				else {
					// add normal brick to the list
					auto& brick_break_sound = m_assetManager.getAsset<SFXAsset>(brick_type.getBreakSoundName());	
					m_bricks.push_back(std::make_unique<NormalBrick>(brick_texture, brick_hit_sound, brick_break_sound, brick_type, brick_position + brick_size / 2.0f, brick_size));
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

	// get all texture refs
	auto &paddle_texture = m_assetManager.getAsset<TextureAsset>(level_config.getPaddleTexture());
	auto &ball_texture = m_assetManager.getAsset<TextureAsset>(level_config.getBallTexture());
	auto &background_texture = m_assetManager.getAsset<TextureAsset>(level_config.getBackgroundTexture());

	// get fonts
	auto& hud_font = m_assetManager.getAsset<FontAsset>("HUDFont");
	auto& text_font = m_assetManager.getAsset<FontAsset>("TextFont");

	// create game objects
	m_paddle = std::make_unique<Paddle>(paddle_texture, level_config.getPaddleSpeed());
	m_ball = std::make_unique<Ball>(ball_texture, level_config.getBallSpeed());
	m_background = std::make_unique<Background>(background_texture, window_size);
	m_hud = std::make_unique<HeadsUpDisplay>(hud_font, m_lives, m_points, m_level, getWindowSize());

	// text objects
	m_roundStartText = std::make_unique<Text>(text_font);
	m_LevelFailedText = std::make_unique<Text>(text_font);
	m_levelPassedText = std::make_unique<Text>(text_font);
	m_lastLevelFinishedText = std::make_unique<Text>(text_font);

	// setup collision detector
	m_collisionDetector = std::make_unique<AABBCollisionDetector>();

	// generate bricks after the background has been set up
	generateBricks();
}

void LevelScene::setupRoundStartText()
{
	auto bg_pos = m_background->getPosition();
	auto bg_size = m_background->getSize();

	// set the text in the middle
	auto text_position = bg_pos;
	auto text_size = glm::vec2(bg_size.x - bg_size.x / 4, 50);

	m_roundStartText->setText("press space to start the game  !");
	m_roundStartText->setColor(SDL_Color{ 255, 255, 255 });
	m_roundStartText->setSize(text_size);
	m_roundStartText->setPosition(text_position);
}

void LevelScene::setupLevelFailedText()
{
	auto bg_pos = m_background->getPosition();
	auto bg_size = m_background->getSize();

	// set the text in the middle
	auto text_position = bg_pos;
	auto text_size = glm::vec2(bg_size.x - bg_size.x / 10.0f, 50);

	m_LevelFailedText->setText("Level failed  !  Press space to restart  !");
	m_LevelFailedText->setColor(SDL_Color{ 255, 255, 255 });
	m_LevelFailedText->setSize(text_size);
	m_LevelFailedText->setPosition(text_position);
}

void LevelScene::setupLevelPassedText()
{
	auto bg_pos = m_background->getPosition();
	auto bg_size = m_background->getSize();

	// set the text in the middle
	auto text_position = bg_pos;
	auto text_size = glm::vec2(bg_size.x - bg_size.x / 10.0f, 50);

	m_levelPassedText->setText("Level passed ! Press space to advance to the next level !");
	m_levelPassedText->setColor(SDL_Color{ 255, 255, 255 });
	m_levelPassedText->setSize(text_size);
	m_levelPassedText->setPosition(text_position);
}

void LevelScene::setupLastLevelPassedText()
{
	auto bg_pos = m_background->getPosition();
	auto bg_size = m_background->getSize();

	// set the text in the middle
	auto text_position = bg_pos;
	auto text_size = glm::vec2(bg_size.x - bg_size.x / 10.0f, 50);

	m_lastLevelFinishedText->setText("Last level finished  ! Press space to return to main menu  !");
	m_lastLevelFinishedText->setColor(SDL_Color{ 255, 255, 255 });
	m_lastLevelFinishedText->setSize(text_size);
	m_lastLevelFinishedText->setPosition(text_position);
}

void LevelScene::setupWallPositionedObjects()
{
	// use background position to setup wall objects
	// value of 10 used for width/height of vertical/horizontal walls
	constexpr auto WALL_SIZE = 20;

	auto bg_pos = m_background->getPosition();
	auto bg_size = m_background->getSize();

	auto bg_top_pos = m_background->getCenterTopPosition();
	auto bg_bottom_pos = m_background->getCenterBottomPosition();
	auto bg_left_pos = m_background->getCenterLeftSidePosition();
	auto bg_right_pos = m_background->getCenterRightSidePosition();

	// size and offset for left and right
	auto vertical_size = glm::vec2(WALL_SIZE, bg_size.y);
	auto vertical_offset = glm::vec2(WALL_SIZE, 0) / 2.0f;

	// size and offset for top and bottom
	auto horizontal_size = glm::vec2(bg_size.x, WALL_SIZE);
	auto horizontal_offset = glm::vec2(0, WALL_SIZE) / 2.0f;

	m_bottomWall.setSize(horizontal_size);
	m_bottomWall.setPosition(bg_bottom_pos + horizontal_offset);
	
	m_topWall.setSize(horizontal_size);
	m_topWall.setPosition(bg_top_pos - horizontal_offset);

	m_leftWall.setSize(vertical_size);
	m_leftWall.setPosition(bg_left_pos - vertical_offset);

	m_rightWall.setSize(vertical_size);
	m_rightWall.setPosition(bg_right_pos + vertical_offset);
}

void LevelScene::removeLifeAndResetObjects()
{
	// TODO: implement reseting of the objects
	m_lives--;

	if (m_lives == 0) {
		// game over - show game over text
		m_state = LevelState::LevelFailed;
	}
	else {
		m_state = LevelState::Starting;
	}

	// reset ball, paddle and starting text
	m_ball->reset();
	m_paddle->reset();
}

void LevelScene::setupAdvancingToNextLevel()
{
	if (isLastLevel()) {
		m_state = LevelState::FinishedLastLevel;
	}
	else {
		m_state = LevelState::Finished;
	}
}

void LevelScene::advanceToNextLevel()
{
	auto& scene_manager = getGameRef().getSceneManager();

	// push new scene to the scene manager and set it as current
	if (m_state == LevelState::FinishedLastLevel) {
		// switch to main menu
		scene_manager.setCurrentScene("MainMenuScene");
	}
	else {
		// advance to the next level
		auto next_level = m_level + 1;
		std::stringstream level_ss;

		level_ss << "Level" << next_level << "Scene";

		auto next_level_scene = level_ss.str();

		// add the new level to the SceneManager
		scene_manager.addScene<LevelScene>(next_level_scene, getGameRef(), next_level);
		scene_manager.setCurrentScene(next_level_scene);
	}

	// reset this level after switching to the next one
	resetLevel();
}

void LevelScene::resetLevel()
{
	// reset all objects
	m_ball->reset();
	m_paddle->reset();

	for (auto& brick : m_bricks) {
		brick->reset();
	}

	// reset level data
	m_points = 0;
	m_lives = 3;

	// reset level state to the start
	m_state = LevelState::Starting;
}

void LevelScene::checkCollisions()
{
	checkPaddleCollision();
	checkWallCollision();
	checkBricksCollision();
}

void LevelScene::checkPaddleCollision()
{
	if (m_collisionDetector->checkCollision(*m_ball, *m_paddle)) {
		m_ball->setDirection(glm::normalize(glm::vec2(randomFloatInRange(-1.0f, 1.0f), -1)));
	}
}

void LevelScene::checkWallCollision()
{
	auto ball_dir = m_ball->getDirection();

	if (m_collisionDetector->checkCollision(dynamic_cast<PositionedObject2D&>(*m_ball), m_bottomWall)) {
		// remove one life
		// if ran out of lives - game over
		removeLifeAndResetObjects();
	}
	if (m_collisionDetector->checkCollision(*m_ball, m_topWall)) {
		// won the game - go to next level
		setupAdvancingToNextLevel();
	}
	if (m_collisionDetector->checkCollision(*m_ball, m_leftWall) || m_collisionDetector->checkCollision(*m_ball, m_rightWall)) {
		// leave direction Y, change X to other side
		m_ball->setDirection(glm::normalize(glm::vec2(ball_dir.x * -1, ball_dir.y)));
	}
}

void LevelScene::checkBricksCollision()
{
	for (auto& brick : m_bricks) {
		if (!brick->isBroken()) {
			if (m_collisionDetector->checkCollision(*m_ball, *brick)) {
				m_ball->setDirection(glm::normalize(glm::vec2(randomFloatInRange(-1.0f, 1.0f), 1)));
				brick->hit();

				// if the brick has just been broken - add the break score to the level points
				// only normal brick can be broken - valid cast
				if (brick->isBroken()) {
					auto &normal_brick = dynamic_cast<NormalBrick&>(*brick);
					auto break_score = normal_brick.getBreakScore();

					m_points += break_score;
				}
			}
		}
	}
}

void LevelScene::renderLevelBackground(SDL_Renderer* renderer)
{
	m_background->render(renderer);
}

void LevelScene::renderLevelBricks(SDL_Renderer* renderer)
{
	for (auto& brick : m_bricks) {
		if (!brick->isBroken()) {
			brick->render(renderer);
		}
	}
}

void LevelScene::renderPaddle(SDL_Renderer* renderer)
{
	m_paddle->render(renderer);
}

void LevelScene::renderBall(SDL_Renderer* renderer)
{
	if (!isLevelFinished()) {
		m_ball->render(renderer);
	}
}

void LevelScene::renderHUD(SDL_Renderer* renderer)
{
	m_hud->render(renderer);
}

void LevelScene::renderRoundStartText(SDL_Renderer* renderer)
{
	if (m_state == LevelState::Starting) {
		m_roundStartText->render(renderer);
	}
}

void LevelScene::renderLevelFailedText(SDL_Renderer* renderer)
{
	if (m_state == LevelState::LevelFailed) {
		m_LevelFailedText->render(renderer);
	}
}

void LevelScene::renderLevelPassedText(SDL_Renderer* renderer)
{
	if (m_state == LevelState::Finished) {
		m_levelPassedText->render(renderer);
	}
}

void LevelScene::renderLastLevelFinishedText(SDL_Renderer* renderer)
{
	if (m_state == LevelState::FinishedLastLevel) {
		m_lastLevelFinishedText->render(renderer);
	}
}

bool LevelScene::isLastLevel() const
{
	return m_level == MAX_LEVEL;
}

bool LevelScene::isLevelFinished() const
{
	return m_state == LevelState::Finished || m_state == LevelState::FinishedLastLevel;
}

glm::ivec2 LevelScene::getWindowSize()
{
	glm::ivec2 window_size = glm::ivec2(0);
	SDL_GetWindowSize(getGameRef().getWindow(), &window_size.x, &window_size.y);

	return window_size;
}
