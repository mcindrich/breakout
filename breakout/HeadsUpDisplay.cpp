#include "HeadsUpDisplay.h"

#include <sstream>

#include <SDL_image.h>
#include <SDL_ttf.h>

HeadsUpDisplay::HeadsUpDisplay(FontAsset &font, unsigned int& lives_ref, unsigned int& points_ref, unsigned int& level_ref, glm::vec2 window_size)
	: m_livesRef(lives_ref), m_pointsRef(points_ref), m_levelRef(level_ref), m_livesText(font), m_pointsText(font), m_levelText(font)
{
	auto q = window_size.x / 3 / 4;

	// setup text positions
	m_livesText.setPosition(glm::vec2(q, 0));
	m_pointsText.setPosition(glm::vec2(5 * q, 0));
	m_levelText.setPosition(glm::vec2(9 * q, 0));

	// setup text sizes
	m_livesText.setSize(glm::vec2(2 * window_size.x / 3 / 4, 50));
	m_pointsText.setSize(glm::vec2(2 * window_size.x / 3 / 4, 50));
	m_levelText.setSize(glm::vec2(2 * window_size.x / 3 / 4, 50));

	// setup text colors
	m_livesText.setColor(SDL_Color{ 255, 255, 255 });
	m_pointsText.setColor(SDL_Color{ 255, 255, 255 });
	m_levelText.setColor(SDL_Color{ 255, 255, 255 });
}

void HeadsUpDisplay::render(SDL_Renderer* renderer)
{
	// | -- TEXT -- | -- TEXT -- | -- TEXT -- |
	renderLivesText(renderer);
	renderPointsText(renderer);
	renderLevelText(renderer);
}

void HeadsUpDisplay::renderLivesText(SDL_Renderer* renderer)
{
	std::stringstream ss;

	ss << "LIVES: " << m_livesRef;

	m_livesText.setText(ss.str());
	m_livesText.render(renderer);
}

void HeadsUpDisplay::renderPointsText(SDL_Renderer* renderer)
{
	std::stringstream ss;

	ss << "POINTS: " << m_pointsRef;

	m_pointsText.setText(ss.str());
	m_pointsText.render(renderer);
}

void HeadsUpDisplay::renderLevelText(SDL_Renderer* renderer)
{
	std::stringstream ss;

	ss << "LEVEL: " << m_levelRef;

	m_levelText.setText(ss.str());
	m_levelText.render(renderer);
}
