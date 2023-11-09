#include "Brick.h"

Brick::Brick(TextureAsset& texture, glm::vec2 position, glm::vec2 size, int health) : PositionedTexture2D(texture), m_health(health)
{
	setPosition(position);
	setSize(size);
}

bool Brick::isBroken() const
{
	return m_health == 0;
}

unsigned int Brick::getHealth() const
{
	return m_health;
}

void Brick::decrHealth()
{
	--m_health;
}
