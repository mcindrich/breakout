#include "NormalBrick.h"

NormalBrick::NormalBrick(TextureAsset& texture, BrickType& bt, glm::vec2 position, glm::vec2 size) 
	: Brick(texture, position, size, bt.getHitPoints())
{
}

void NormalBrick::hit()
{
	decrHealth();
}
