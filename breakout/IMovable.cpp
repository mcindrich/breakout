#include "IMovable.h"

float IMovable::getSpeed() const
{
    return m_speed;
}

glm::vec2 IMovable::getDirection() const
{
    return m_direction;
}

void IMovable::updatePosition(float delta)
{
    setPosition(getPosition() + (getDirection() * getSpeed() * delta));
}

void IMovable::setSpeed(float speed)
{
    m_speed = speed;
}

void IMovable::setDirection(glm::vec2 direction)
{
    m_direction = glm::normalize(direction);
}
