#include "PositionedObject2D.h"

PositionedObject2D::PositionedObject2D() : m_position(0), m_size(0)
{
}

PositionedObject2D::PositionedObject2D(glm::vec2 position, glm::vec2 size) : m_position(position), m_size(size)
{
}

glm::vec2 PositionedObject2D::getPosition() const
{
	return m_position;
}

glm::vec2 PositionedObject2D::getSize() const
{
	return m_size;
}

void PositionedObject2D::setPosition(glm::vec2 position)
{
	m_position = position;
}

void PositionedObject2D::setSize(glm::vec2 size)
{
	m_size = size;
}

glm::vec2 PositionedObject2D::getTopLeftPosition() const
{
	return m_position - m_size / 2.0f;
}

void PositionedObject2D::setPositionByTopLeftCorner(glm::vec2 top_left)
{
	m_position = top_left + m_size / 2.0f;
}

glm::vec2 PositionedObject2D::getCenterTopPosition() const
{
	return getPosition() - glm::vec2(0, getSize().y / 2.0f);
}

glm::vec2 PositionedObject2D::getCenterBottomPosition() const
{
	return getPosition() + glm::vec2(0, getSize().y / 2.0f);
}

glm::vec2 PositionedObject2D::getCenterLeftSidePosition() const
{
	return getPosition() - glm::vec2(getSize().x / 2.0f, 0);
}

glm::vec2 PositionedObject2D::getCenterRightSidePosition() const
{
	return getPosition() + glm::vec2(getSize().x / 2.0f, 0);
}

float PositionedObject2D::getLeftX() const
{
	return getCenterLeftSidePosition().x;
}

float PositionedObject2D::getRightX() const
{
	return getCenterRightSidePosition().x;
}

float PositionedObject2D::getTopY() const
{
	return getCenterTopPosition().y;
}

float PositionedObject2D::getBottomY() const
{
	return getCenterBottomPosition().y;
}
