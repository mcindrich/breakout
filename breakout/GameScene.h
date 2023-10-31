#pragma once
#include "IScene.h"
#include "TextureManager.h"
#include "Level.h"

#include "tinyxml2.h"

class Game;

class GameScene :
    public IScene
{
public:
    GameScene(Game *game);

    virtual void processEvents() override;

    virtual void update(float delta) override;

    virtual void render(SDL_Renderer *renderer) override;

private:
    friend class Game;

    // rendering helpers
    void renderLevelBackground(SDL_Renderer* renderer);
    void renderLevelBricks(SDL_Renderer* renderer);
    void renderPaddle(SDL_Renderer* renderer);
    void renderBall(SDL_Renderer* renderer);

    tinyxml2::XMLDocument m_levelDocument;
    Level* m_level;

    // texture loader / manager
    TextureManager m_texManager;
};