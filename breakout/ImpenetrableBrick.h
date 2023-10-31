#pragma once

#include "Brick.h"
#include "BrickType.h"
#include "TextureManager.h"

#include <glm/glm.hpp>

class ImpenetrableBrick :
    public Brick
{
public:
    ImpenetrableBrick(TextureManager& tm, BrickType& bt, glm::vec2 position, glm::ivec2 size);

    virtual void hit() override;
};

