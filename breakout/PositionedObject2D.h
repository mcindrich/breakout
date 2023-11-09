#pragma once

#include <glm/glm.hpp>

class PositionedObject2D
{
public:
	PositionedObject2D();
	PositionedObject2D(glm::vec2 position, glm::vec2 size);

	glm::vec2 getPosition() const;
	glm::vec2 getSize() const;

protected:
	void setPosition(glm::vec2 position);
	void setSize(glm::vec2 size);

private:
	glm::vec2 m_position;
	glm::vec2 m_size;
};

