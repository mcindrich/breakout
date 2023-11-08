#include "HeadsUpDisplay.h"

HeadsUpDisplay::HeadsUpDisplay(unsigned int& lives_ref, unsigned int& points_ref, unsigned int& level_ref, glm::vec2 window_size) 
	: m_livesRef(lives_ref), m_pointsRef(points_ref), m_levelRef(level_ref), m_font(nullptr)
{
	setPosition(glm::vec2(0, 0));
}

void HeadsUpDisplay::setFont(FontAsset& font_asset)
{
	m_font = font_asset.getFont();
}

void HeadsUpDisplay::render(SDL_Renderer* renderer)
{
}
