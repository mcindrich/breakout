#include "Brick.h"

Brick::Brick(SDL_Texture* texture, glm::vec2 position, glm::vec2 size, int health) : m_position(position), m_size(size), m_health(health)
{
	setTexture(texture);
}

void Brick::render(SDL_Renderer* renderer)
{
	// render on position
	SDL_FRect rect;

	rect = { m_position.x, m_position.y, m_size.x, m_size.y };

	SDL_RenderCopyF(renderer, getTexture(), NULL, &rect);
}

bool Brick::isBroken() const
{
	return m_health == 0;
}

unsigned int Brick::getHealth() const
{
	return m_health;
}

glm::vec2 Brick::getPosition()
{
	return m_position;
}

void Brick::decrHealth()
{
	--m_health;
}
