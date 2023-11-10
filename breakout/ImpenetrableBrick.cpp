#include "ImpenetrableBrick.h"

ImpenetrableBrick::ImpenetrableBrick(TextureAsset& texture, SFXAsset& hit_sound, BrickType& bt, glm::vec2 position, glm::vec2 size)
	: Brick(texture, hit_sound, position, size, bt.getHitPoints())
{
}

unsigned int ImpenetrableBrick::getBreakScore() const
{
	return 0;
}

void ImpenetrableBrick::hitEvent()
{
	// don't do anything for this brick - it can't be damaged
}
