#include "Ball.h"
#include "ImageAsset.h"

#include <stdexcept>

Ball::Ball(TextureManager& texture_manager, const std::string& ball_texture, const float speed)
{
	auto texture = texture_manager.getTexturePtr(ball_texture);
	setTexture(texture);
	setSpeed(speed);
	setPosition(glm::vec2(400, 650));
	setSize(glm::vec2(10, 10));

	// generate starting random direction
	generateRandomDirection();
}

void Ball::render(SDL_Renderer* renderer)
{
	// render on position
	SDL_FRect rect;

	rect = { getPosition().x - getSize().x / 2, getPosition().y - getSize().y / 2, getSize().x, getSize().y};

	SDL_RenderCopyF(renderer, getTexture(), NULL, &rect);
}

void Ball::generateRandomDirection()
{
	auto random_x = -0.5;
	setDirection(glm::normalize(glm::vec2(random_x, 1)));
}
