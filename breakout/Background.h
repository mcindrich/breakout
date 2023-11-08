#pragma once

#include "TextureManager.h"
#include "IRenderObject.h"

#include <glm/glm.hpp>

class Background :
    public IRenderObject
{
public:
    Background(TextureManager &texture_manager, const std::string &background_texture, glm::vec2 window_size);
};

