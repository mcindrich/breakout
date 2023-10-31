#include "TextureManager.h"

#include <stdexcept>

void TextureManager::loadTexture(SDL_Renderer* renderer, const std::string& fpath, const std::string& name)
{
	auto texture = IMG_LoadTexture(renderer, fpath.c_str());
	if (!texture) {
		throw std::runtime_error("Unable to load texture");
	}

	m_textures[name] = TextureUniquePtr(texture, SDL_DestroyTexture);
}

TextureUniquePtr& TextureManager::getTexture(const std::string& name)
{
	return m_textures.at(name);
}
