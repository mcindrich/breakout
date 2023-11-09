#pragma once

#include "Brick.h"
#include "BrickType.h"

#include <glm/glm.hpp>

class NormalBrick :
    public Brick
{
public:
    NormalBrick(TextureAsset& texture, BrickType &bt, glm::vec2 position, glm::vec2 size);

    virtual void hit() override;

private:
};

