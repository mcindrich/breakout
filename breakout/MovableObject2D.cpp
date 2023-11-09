#include "MovableObject2D.h"

float MovableObject2D::getSpeed() const
{
    return m_speed;
}

glm::vec2 MovableObject2D::getDirection() const
{
    return m_direction;
}

void MovableObject2D::updatePosition(float delta)
{
    setPosition(getPosition() + (getDirection() * getSpeed() * delta));
}

void MovableObject2D::setSpeed(float speed)
{
    m_speed = speed;
}

void MovableObject2D::setDirection(glm::vec2 direction)
{
    m_direction = glm::normalize(direction);
}
