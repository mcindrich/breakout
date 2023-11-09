#pragma once

#include "PositionedTexture2D.h"
#include "TextureAsset.h"

#include <glm/glm.hpp>

class Background :
    public PositionedTexture2D
{
public:
    Background(TextureAsset& texture, glm::vec2 window_size);
};

