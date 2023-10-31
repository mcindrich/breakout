#include "NormalBrick.h"

NormalBrick::NormalBrick(TextureManager& tm, BrickType& bt, glm::vec2 position, glm::ivec2 size) 
	: Brick(tm.getTexture(bt.getBrickTextureName()).get(), position, size, bt.getHitPoints())
{
}

void NormalBrick::hit()
{
	decrHealth();
}
