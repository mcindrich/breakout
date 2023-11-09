#include "ImpenetrableBrick.h"

ImpenetrableBrick::ImpenetrableBrick(TextureAsset& texture, BrickType& bt, glm::vec2 position, glm::vec2 size) 
	: Brick(texture, position, size, bt.getHitPoints())
{
}

void ImpenetrableBrick::hit()
{
	// don't do anything for this brick
}
