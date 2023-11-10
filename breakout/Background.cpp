#include "Background.h"

#include <stdexcept>
#include <glm/glm.hpp>

constexpr auto BACKGROUND_OFFSET = 50;
glm::vec2 OFFSET_VEC = glm::vec2(0, BACKGROUND_OFFSET);

Background::Background(TextureAsset& texture, glm::vec2 window_size) : PositionedTexture2D(texture)
{
	setSize(window_size - OFFSET_VEC);
	setPositionByTopLeftCorner(OFFSET_VEC);
}
