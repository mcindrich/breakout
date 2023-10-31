#pragma once

#include "Brick.h"
#include "BrickType.h"
#include "TextureManager.h"

#include <glm/glm.hpp>

class NormalBrick :
    public Brick
{
public:
    NormalBrick(TextureManager &tm, BrickType &bt, glm::vec2 position, glm::ivec2 size);

    virtual void hit() override;

private:
};

