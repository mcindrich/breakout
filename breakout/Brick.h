#pragma once

#include "PositionedTexture2D.h"

#include <SDL_image.h>

#include <glm/glm.hpp>

class Brick :
    public PositionedTexture2D
{
public:
    Brick(TextureAsset& texture, glm::vec2 position, glm::vec2 size, int health);

    bool isBroken() const;
    unsigned int getHealth() const;
    
    virtual void hit() = 0;

protected:
    void decrHealth();

private:
    unsigned int m_health;
};

