#pragma once

#include <glm/glm.hpp>

class PositionedObject2D
{
public:
	PositionedObject2D();
	PositionedObject2D(glm::vec2 position, glm::vec2 size);

	glm::vec2 getPosition() const;
	glm::vec2 getSize() const;

	void setPosition(glm::vec2 position);
	void setSize(glm::vec2 size);

	glm::vec2 getTopLeftPosition() const;
	void setPositionByTopLeftCorner(glm::vec2 top_left);

	// sides API
	glm::vec2 getCenterTopPosition() const;
	glm::vec2 getCenterBottomPosition() const;
	glm::vec2 getCenterLeftSidePosition() const;
	glm::vec2 getCenterRightSidePosition() const;

	float getLeftX() const;
	float getRightX() const;
	float getTopY() const;
	float getBottomY() const;

private:
	glm::vec2 m_position;
	glm::vec2 m_size;
};

