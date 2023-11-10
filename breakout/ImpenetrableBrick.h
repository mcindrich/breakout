#pragma once

#include "Brick.h"
#include "BrickType.h"

#include <glm/glm.hpp>

class ImpenetrableBrick :
    public Brick
{
public:
    ImpenetrableBrick(TextureAsset& texture, SFXAsset &hit_sound, BrickType& bt, glm::vec2 position, glm::vec2 size);

    virtual unsigned int getBreakScore() const override;

protected:
    virtual void hitEvent() override;
};

