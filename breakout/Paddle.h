#pragma once

#include "IRenderObject.h"
#include "TextureManager.h"

#include <glm/glm.hpp>

class Paddle : public IRenderObject
{
public:
	Paddle(TextureManager &tm);

	virtual void render(SDL_Renderer* renderer) override;

	void moveRight(float delta);
	void moveLeft(float delta);

private:
	glm::vec2 m_position;
	glm::ivec2 m_size;
};

