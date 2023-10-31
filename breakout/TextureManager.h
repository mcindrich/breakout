#pragma once

#include <map>
#include <string>
#include <memory>
#include <functional>

#include <SDL_image.h>
#include <SDL_render.h>

using TextureDeleter = std::function<void(SDL_Texture*)>;
using TextureUniquePtr = std::unique_ptr<SDL_Texture, TextureDeleter>;

class TextureManager
{
public:
	void loadTexture(SDL_Renderer *renderer, const std::string& fpath, const std::string& name);

	TextureUniquePtr& getTexture(const std::string& name);

private:
	std::map<std::string, TextureUniquePtr> m_textures;
};

