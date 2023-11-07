#pragma once
#include "UIScene.h"

class LevelScene;

class HUDScene :
    public UIScene
{
public:
	HUDScene(Game* game, LevelScene *level_scene);

	virtual void update(float delta) override;
	virtual void render(SDL_Renderer* renderer) override;

private:
	LevelScene* m_levelScene;
};

