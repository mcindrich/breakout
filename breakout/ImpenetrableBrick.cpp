#include "ImpenetrableBrick.h"

ImpenetrableBrick::ImpenetrableBrick(TextureManager& tm, BrickType& bt, glm::vec2 position, glm::ivec2 size) 
	: Brick(tm.getTexture(bt.getBrickTextureName()).get(), position, size, bt.getHitPoints())
{
}

void ImpenetrableBrick::hit()
{
	// don't do anything for this brick
}
