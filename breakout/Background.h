#pragma once

#include "TextureManager.h"
#include "IRenderObject.h"

#include <glm/glm.hpp>

class Background :
    public IRenderObject
{
public:
    Background(TextureManager& tm, const std::string &bg_tex_name, glm::vec2 window_size);

    virtual void render(SDL_Renderer* renderer) override;

    glm::vec2 getSize() const;
    glm::vec2 getPosition() const;

private:
    glm::vec2 m_size;
    glm::vec2 m_position;
};

