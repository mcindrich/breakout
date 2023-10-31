#pragma once

#include "IRenderObject.h"

#include <SDL_image.h>

#include <glm/glm.hpp>

class Brick :
    public IRenderObject
{
public:
    Brick(SDL_Texture* texture, glm::vec2 position, glm::vec2 size, int health);

    virtual void render(SDL_Renderer* renderer) override;

    bool isBroken() const;
    unsigned int getHealth() const;

    glm::vec2 getPosition();
    
    virtual void hit() = 0;

protected:
    void decrHealth();

private:
    glm::vec2 m_position;
    glm::vec2 m_size;
    unsigned int m_health;
};

