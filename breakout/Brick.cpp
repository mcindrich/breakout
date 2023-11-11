#include "Brick.h"

#include <SDL_mixer.h>

Brick::Brick(TextureAsset& texture, SFXAsset& hit_sound, glm::vec2 position, glm::vec2 size, int health)
	: PositionedTexture2D(texture), m_health(health), m_initialHealth(health), m_hitSound(hit_sound)
{
	setSize(size);
	setPosition(position);
}

bool Brick::isBroken() const
{
	return m_health == 0;
}

unsigned int Brick::getHealth() const
{
	return m_health;
}

void Brick::hit()
{
	// play hit sound
	auto sfx_chunk = m_hitSound.getSFXChunk();
	Mix_PlayChannel(-1, sfx_chunk, 0);

	// use overriden method from subclasses to react to an event
	hitEvent();
}

void Brick::reset()
{
	m_health = m_initialHealth;
}

void Brick::decrHealth()
{
	--m_health;
}
