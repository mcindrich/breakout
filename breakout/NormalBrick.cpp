#include "NormalBrick.h"

NormalBrick::NormalBrick(TextureAsset& texture, SFXAsset& hit_sound, SFXAsset& break_sound, BrickType& bt, glm::vec2 position, glm::vec2 size)
	: Brick(texture, hit_sound, position, size, bt.getHitPoints()), m_breakSound(break_sound), m_breakScore(bt.getBreakScore())
{
}

unsigned int NormalBrick::getBreakScore() const
{
	return m_breakScore;
}

void NormalBrick::hitEvent()
{
	decrHealth();
	if (getHealth() == 0) {
		// play break sound
		auto sfx_chunk = m_breakSound.getSFXChunk();
		Mix_PlayChannel(-1, sfx_chunk, 0);
	}
}
