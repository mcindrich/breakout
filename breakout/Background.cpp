#include "Background.h"
#include "ImageAsset.h"

#include <stdexcept>
#include <glm/glm.hpp>

constexpr auto BACKGROUND_OFFSET = 50;
glm::vec2 OFFSET_VEC = glm::vec2(0, BACKGROUND_OFFSET);

Background::Background(TextureManager& texture_manager, const std::string& background_texture, glm::vec2 window_size)
{
	auto texture = texture_manager.getTexturePtr(background_texture);
	setTexture(texture);
	setPosition(OFFSET_VEC);
	setSize(window_size - OFFSET_VEC);
}
