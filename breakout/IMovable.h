#pragma once

#include "IRenderObject.h"
#include <glm/glm.hpp>

class IMovable : public IRenderObject
{
public:
	void setSpeed(float speed);
	void setDirection(glm::vec2 direction);

	float getSpeed() const;
	glm::vec2 getDirection() const;

	void updatePosition(float delta);

private:
	float m_speed;
	glm::vec2 m_direction;
};

