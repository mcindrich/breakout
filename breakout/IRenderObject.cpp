#include "IRenderObject.h"

void IRenderObject::setTexture(SDL_Texture* texture)
{
    m_texture = texture;
}

SDL_Texture* IRenderObject::getTexture()
{
    return m_texture;
}
