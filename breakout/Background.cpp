#include "Background.h"

#include <glm/glm.hpp>

constexpr auto BACKGROUND_OFFSET = 0;
const glm::vec2 OFFSET_VEC = glm::vec2(BACKGROUND_OFFSET);

Background::Background(TextureManager& tm, const std::string& bg_tex_name, glm::vec2 window_size) : m_size(window_size - OFFSET_VEC), m_position(BACKGROUND_OFFSET)
{
	setTexture(tm.getTexture(bg_tex_name).get());
}

void Background::render(SDL_Renderer* renderer)
{
	SDL_FRect bg_rect;

	bg_rect = { m_position.x, m_position.y, m_size.x, m_size.y };

	SDL_RenderCopyF(renderer, getTexture(), NULL, &bg_rect);
}

glm::vec2 Background::getSize() const
{
	return m_size;
}

glm::vec2 Background::getPosition() const
{
	return m_position;
}
