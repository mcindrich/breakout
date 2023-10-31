#include "Ball.h"

constexpr auto BALL_SPEED = 200;

Ball::Ball(TextureManager& tm) : m_position(400, 650), m_size(10, 10), m_direction(1, 1)
{
	setTexture(tm.getTexture("ball.png").get());
}

void Ball::render(SDL_Renderer* renderer)
{
	// render on position
	SDL_Rect rect;

	rect = { (int)m_position.x - m_size.x / 2, (int)m_position.y - m_size.y / 2, m_size.x, m_size.y };

	SDL_RenderCopy(renderer, getTexture(), NULL, &rect);
}

void Ball::setDirection(glm::vec2 dir)
{
	m_direction = glm::normalize(dir);
}

void Ball::update(float delta)
{
	m_position = m_direction * delta * (float)BALL_SPEED;
}
