#include "Paddle.h"

constexpr auto PADDLE_SPEED = 500;

Paddle::Paddle(TextureManager& tm) : m_position(400, 780), m_size(60, 10)
{
	setTexture(tm.getTexture("paddle.png").get());
}

void Paddle::render(SDL_Renderer* renderer)
{
	// render on position
	SDL_Rect rect;

	rect = { (int)m_position.x - m_size.x / 2, (int)m_position.y - m_size.y / 2, m_size.x, m_size.y};

	SDL_RenderCopy(renderer, getTexture(), NULL, &rect);
}

void Paddle::moveRight(float delta)
{
	auto move_delta = PADDLE_SPEED * delta;
	if (!(m_position.x + move_delta > 800 - m_size.x / 2)) {
		m_position.x += move_delta;
	}
}

void Paddle::moveLeft(float delta)
{
	auto move_delta = PADDLE_SPEED * delta;
	if (!(m_position.x - move_delta < m_size.x / 2)) {
		m_position.x -= move_delta;
	}
}
