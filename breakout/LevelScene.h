#pragma once

#include "Scene.h"
#include "AssetManager.h"
#include "Paddle.h"
#include "Ball.h"
#include "Background.h"
#include "Brick.h"
#include "Timer.h"
#include "HeadsUpDisplay.h"
#include "ICollisionDetector.h"

#include <vector>
#include <memory>

class LevelScene :
    public Scene
{
public:
    LevelScene(Game &game, unsigned int level, unsigned int points, unsigned int lives);

    virtual void processEvents() override;

    virtual void update(float delta) override;

    virtual void render(SDL_Renderer* renderer) override;

private:
    enum class LevelState {
        Starting,
        Playing,
        LevelFailed,
        Finished,
        FinishedLastLevel,
    };

    // initialization helpers
    void loadLevelConfigurationAsset(unsigned int level);
    void loadBackgroundAsset();
    void loadBrickTextureAssets();
    void loadPaddleTextureAsset();
    void loadBallTextureAsset();
    void loadBrickSFXAssets();
    void loadFontAssets();
    void generateBricks();
    void createGameObjects();
    void setupRoundStartText();
    void setupLevelFailedText();
    void setupLevelPassedText();
    void setupLastLevelPassedText();
    void setupWallPositionedObjects();

    // level manipulation
    void removeLifeAndResetObjects();
    void setupAdvancingToNextLevel();
    void advanceToNextLevel();
    void resetLevel();
    void goBackToMainMenu();

    // collision handling
    void checkCollisions(float delta);
    void checkPaddleCollision();
    void checkWallCollision(float delta);
    void checkBricksCollision();

    // rendering helpers
    void renderLevelBackground(SDL_Renderer* renderer);
    void renderLevelBricks(SDL_Renderer* renderer);
    void renderPaddle(SDL_Renderer* renderer);
    void renderBall(SDL_Renderer* renderer);
    void renderHUD(SDL_Renderer* renderer);
    void renderRoundStartText(SDL_Renderer* renderer);
    void renderLevelFailedText(SDL_Renderer* renderer);
    void renderLevelPassedText(SDL_Renderer* renderer);
    void renderLastLevelFinishedText(SDL_Renderer* renderer);

    bool isLastLevel() const;
    bool isLevelFinished() const;

    // window helpers
    glm::ivec2 getWindowSize();

    AssetManager m_assetManager; // handles loading of all assets (textures, fonts, sounds etc.)

    // main game objects - paddle, ball, background, bricks and HUD
    std::unique_ptr<Paddle> m_paddle;
    std::unique_ptr<Ball> m_ball;
    std::unique_ptr<Background> m_background;
    std::unique_ptr<HeadsUpDisplay> m_hud;
    std::vector<std::unique_ptr<Brick>> m_bricks;

    // HUD data
    unsigned int m_level;
    unsigned int m_points;
    unsigned int m_lives;

    // level state
    LevelState m_state;

    // text before starting a round
    std::unique_ptr<Text> m_roundStartText;

    // text for game over
    std::unique_ptr<Text> m_LevelFailedText;

    // text for when the level is finished
    std::unique_ptr<Text> m_levelPassedText;

    // text for when the last level is finished
    std::unique_ptr<Text> m_lastLevelFinishedText;

    // collision detector between objects
    std::unique_ptr<ICollisionDetector> m_collisionDetector;

    // invisible wall objects used for checking ball collision
    PositionedObject2D m_topWall;
    PositionedObject2D m_bottomWall;
    PositionedObject2D m_leftWall;
    PositionedObject2D m_rightWall;
};

