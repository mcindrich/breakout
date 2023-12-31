#pragma once

#include "UIScene.h"

class MainMenuScene :
    public UIScene
{
public:
    MainMenuScene(Game &game);

    virtual void update(float delta) override;
    virtual void render(SDL_Renderer* renderer) override;
};

