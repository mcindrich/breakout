#pragma once

#include "Brick.h"
#include "BrickType.h"
#include "SFXAsset.h"

#include <glm/glm.hpp>

class NormalBrick :
    public Brick
{
public:
    NormalBrick(TextureAsset& texture, SFXAsset &hit_sound, SFXAsset &break_sound, BrickType &bt, glm::vec2 position, glm::vec2 size);

    virtual unsigned int getBreakScore() const override;

protected:
    virtual void hitEvent() override;

private:
    unsigned int m_breakScore;
    SFXAsset& m_breakSound;
};

