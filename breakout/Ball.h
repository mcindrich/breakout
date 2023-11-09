#pragma once

#include "MovableTexture2D.h"

#include <glm/glm.hpp>

class Ball
	: public MovableTexture2D
{
public:
	Ball(TextureAsset& texture, const float speed);

	virtual void render(SDL_Renderer* renderer) override;

private:
	void generateRandomDirection();
};

