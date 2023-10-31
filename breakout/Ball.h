#pragma once

#include "TextureManager.h"
#include "IRenderObject.h"

#include <glm/glm.hpp>

class Ball :
    public IRenderObject
{
public:
	Ball(TextureManager& tm);

	virtual void render(SDL_Renderer* renderer) override;

	void setDirection(glm::vec2 dir);
	void update(float delta);

private:
	glm::vec2 m_direction;
	glm::vec2 m_position;
	glm::ivec2 m_size;
};

