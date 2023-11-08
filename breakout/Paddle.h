#pragma once

#include "IRenderObject.h"
#include "IMovable.h"
#include "TextureManager.h"

#include <glm/glm.hpp>

class Paddle : public IMovable
{
public:
	Paddle(TextureManager& texture_manager, const std::string &paddle_texture, const float speed);

	virtual void render(SDL_Renderer* renderer) override;

	void moveRight(float delta);
	void moveLeft(float delta);
};

