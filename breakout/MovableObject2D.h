#pragma once

#include "IRenderable.h"
#include "PositionedObject2D.h"

#include <glm/glm.hpp>

class MovableObject2D : public PositionedObject2D
{
public:
	MovableObject2D() = default;

	void setSpeed(float speed);
	void setDirection(glm::vec2 direction);

	float getSpeed() const;
	glm::vec2 getDirection() const;

	void updatePosition(float delta);

private:
	float m_speed;
	glm::vec2 m_direction;
};

