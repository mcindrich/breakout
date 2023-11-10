#include "Ball.h"
#include "Common.h"

#include <stdexcept>

Ball::Ball(TextureAsset& texture, const float speed) : MovableTexture2D(texture)
{
	setSpeed(speed);
	setSize(glm::vec2(10, 10));
	setPosition(glm::vec2(400, 650));
	setDirection(glm::vec2(0, 0));

	// generate starting random direction
	generateRandomDirection();
}

void Ball::generateRandomDirection()
{
	auto random_x = randomFloatInRange(-1.0f, 1.0f);
	setDirection(glm::normalize(glm::vec2(random_x, 1)));
}