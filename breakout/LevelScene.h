#pragma once

#include "IScene.h"
#include "TextureManager.h"
#include "Paddle.h"
#include "Ball.h"
#include "Background.h"
#include "Brick.h"
#include "Timer.h"

#include <vector>
#include <memory>

class HUDScene;

class LevelScene :
    public IScene
{
public:
    LevelScene(Game *game, unsigned int level);

    virtual void processEvents() override;

    virtual void update(float delta) override;

    virtual void render(SDL_Renderer* renderer) override;

private:
    friend class Game;

    // rendering helpers
    void renderLevelBackground(SDL_Renderer* renderer);
    void renderLevelBricks(SDL_Renderer* renderer);
    void renderPaddle(SDL_Renderer* renderer);
    void renderBall(SDL_Renderer* renderer);
    void renderHUD(SDL_Renderer* renderer);

    TextureManager m_texManager; // handles loading of textures

    std::string m_levelBackground; // Level background path extracted from level configuration

    // main game objects - paddle, ball and bricks
    std::unique_ptr<Paddle> m_paddle;
    std::unique_ptr<Ball> m_ball;
    std::unique_ptr<Background> m_background;
    std::vector<std::vector<std::unique_ptr<Brick>>> m_bricks;

    std::unique_ptr<HUDScene> m_hudScene;

    Timer m_startTimer;
    unsigned int m_startCounter;
};

