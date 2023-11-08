#include "Brick.h"

Brick::Brick(TextureManager& texture_manager, const std::string brick_texture, glm::vec2 position, glm::vec2 size, int health) : m_health(health)
{
	auto texture = texture_manager.getTexturePtr(brick_texture);
	setTexture(texture);
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
