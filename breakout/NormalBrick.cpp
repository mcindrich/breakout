#include "NormalBrick.h"

NormalBrick::NormalBrick(TextureManager& texture_manager, BrickType& bt, glm::vec2 position, glm::ivec2 size) 
	: Brick(texture_manager, bt.getBrickTextureName(), position, size, bt.getHitPoints())
{
}

void NormalBrick::hit()
{
	decrHealth();
}
