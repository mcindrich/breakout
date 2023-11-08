#include "HeadsUpDisplay.h"

#include <sstream>

#include <SDL_image.h>
#include <SDL_ttf.h>

HeadsUpDisplay::HeadsUpDisplay(AssetManager &asset_manager, unsigned int& lives_ref, unsigned int& points_ref, unsigned int& level_ref, glm::vec2 window_size)
	: m_livesRef(lives_ref), m_pointsRef(points_ref), m_levelRef(level_ref), m_font(asset_manager.getAsset<FontAsset>("HUDFont"))
{
	auto q = window_size.x / 3 / 4;

	setSize(glm::vec2(2 * window_size.x / 3 / 4, 50));

	m_livesTextPosition = glm::vec2(q, 0);
	m_pointsTextPosition = glm::vec2(5 * q, 0);
	m_levelTextPosition = glm::vec2(9 * q, 0);
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
	std::stringstream lives_ss;

	SDL_Color text_color = { 255, 255, 255 };

	lives_ss << "LIVES: " << m_livesRef;

	auto surface = TTF_RenderText_Solid(m_font.getFont(), lives_ss.str().c_str(), text_color);
	auto texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FRect rect = { m_livesTextPosition.x, m_livesTextPosition.y, getSize().x, getSize().y };

	SDL_RenderCopyF(renderer, texture, NULL, &rect);
}

void HeadsUpDisplay::renderPointsText(SDL_Renderer* renderer)
{
	std::stringstream points_ss;

	SDL_Color text_color = { 255, 255, 255 };

	points_ss << "POINTS: " << m_pointsRef;

	auto surface = TTF_RenderText_Solid(m_font.getFont(), points_ss.str().c_str(), text_color);
	auto texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FRect rect = { m_pointsTextPosition.x, m_pointsTextPosition.y, getSize().x, getSize().y };

	SDL_RenderCopyF(renderer, texture, NULL, &rect);
}

void HeadsUpDisplay::renderLevelText(SDL_Renderer* renderer)
{
	std::stringstream level_ss;

	SDL_Color text_color = { 255, 255, 255 };

	level_ss << "LEVEL: " << m_levelRef;

	auto surface = TTF_RenderText_Solid(m_font.getFont(), level_ss.str().c_str(), text_color);
	auto texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FRect rect = { m_levelTextPosition.x, m_levelTextPosition.y, getSize().x, getSize().y };

	SDL_RenderCopyF(renderer, texture, NULL, &rect);
}
