#include "IRenderObject.h"

IRenderObject::IRenderObject() : m_texture(nullptr), m_position(0), m_size(0)
{
}

void IRenderObject::render(SDL_Renderer* renderer)
{
	// render on position
	SDL_FRect rect;

	rect = { getPosition().x, getPosition().y, getSize().x, getSize().y};

	SDL_RenderCopyF(renderer, getTexture(), NULL, &rect);
}

glm::vec2 IRenderObject::getPosition() const
{
	return m_position;
}

glm::vec2 IRenderObject::getSize() const
{
	return m_size;
}

IRenderObject::~IRenderObject()
{
}

void IRenderObject::setTexture(SDL_Texture* texture)
{
    m_texture = texture;
}

SDL_Texture* IRenderObject::getTexture()
{
    return m_texture;
}

void IRenderObject::setPosition(glm::vec2 position)
{
	m_position = position;
}

void IRenderObject::setSize(glm::vec2 size)
{
	m_size = size;
}
