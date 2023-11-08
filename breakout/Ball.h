#pragma once

#include "TextureManager.h"
#include "IRenderObject.h"
#include "IMovable.h"

#include <glm/glm.hpp>

class Ball : public IMovable
{
public:
	Ball(TextureManager& texture_manager, const std::string &ball_texture, const float speed);

	virtual void render(SDL_Renderer* renderer) override;

private:
	void generateRandomDirection();
};

