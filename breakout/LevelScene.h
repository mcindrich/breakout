#pragma once

#include "IScene.h"
#include "TextureManager.h"
#include "AssetManager.h"
#include "Paddle.h"
#include "Ball.h"
#include "Background.h"
#include "Brick.h"
#include "Timer.h"
#include "HeadsUpDisplay.h"

#include <vector>
#include <memory>

class LevelScene :
    public IScene
{
public:
    LevelScene(Game &game, unsigned int level);

    virtual void processEvents() override;

    virtual void update(float delta) override;

    virtual void render(SDL_Renderer* renderer) override;

private:
    friend class Game;

    // initialization helpers
    void loadLevelConfigurationAsset(unsigned int level);
    void loadBackgroundAsset();
    void loadBrickImageAssets();
    void loadPaddleImageAsset();
    void loadBallImageAsset();
    void loadBrickSFXAssets();
    void loadFontAssets();
    void generateBricks();
    void createGameObjects();
    void setupStartTimer();
    void setupHUD();

    // rendering helpers
    void renderLevelBackground(SDL_Renderer* renderer);
    void renderLevelBricks(SDL_Renderer* renderer);
    void renderPaddle(SDL_Renderer* renderer);
    void renderBall(SDL_Renderer* renderer);
    void renderHUD(SDL_Renderer* renderer);

    glm::ivec2 getWindowSize();

    AssetManager m_assetManager;

    TextureManager m_textureManager; // handles loading of textures - loads textures only once instead of for example every brick having its own texture

    std::string m_levelBackground; // Level background path extracted from level configuration

    // main game objects - paddle, ball and bricks
    std::unique_ptr<Paddle> m_paddle;
    std::unique_ptr<Ball> m_ball;
    std::unique_ptr<Background> m_background;
    std::vector<std::vector<std::unique_ptr<Brick>>> m_bricks;

    Timer m_startTimer;
    unsigned int m_startCounter;

    // HUD data providers
    unsigned int m_level;
    unsigned int m_points;
    unsigned int m_lives;

    // HUD
    HeadsUpDisplay m_hud;
};

