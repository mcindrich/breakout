#pragma once

#include "Brick.h"
#include "BrickType.h"

#include <glm/glm.hpp>

class ImpenetrableBrick :
    public Brick
{
public:
    ImpenetrableBrick(TextureAsset& texture, BrickType& bt, glm::vec2 position, glm::vec2 size);

    virtual void hit() override;
};

