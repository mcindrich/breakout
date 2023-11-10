#pragma once

#include "PositionedTexture2D.h"
#include "TextureAsset.h"
#include "SFXAsset.h"

#include <SDL_image.h>

#include <glm/glm.hpp>
#include <optional>

class Brick :
    public PositionedTexture2D
{
public:
    Brick(TextureAsset& texture, SFXAsset &hit_sound, glm::vec2 position, glm::vec2 size, int health);

    bool isBroken() const;
    unsigned int getHealth() const;
    
    void hit();

    virtual unsigned int getBreakScore() const = 0;

protected:
    virtual void hitEvent() = 0;

    void decrHealth();

private:
    unsigned int m_health;
    SFXAsset& m_hitSound;
};

