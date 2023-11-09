#include "TextureAsset.h"

#include <stdexcept>

#include <SDL_image.h>

TextureAsset::TextureAsset(SDL_Renderer* renderer) : m_renderer(renderer), m_texture(nullptr)
{
}

void TextureAsset::loadFromFile(const std::string& fpath)
{
    m_texture = IMG_LoadTexture(m_renderer, fpath.c_str());
    if (!m_texture) {
        throw std::runtime_error("Unable to load texture " + fpath);
    }
}

SDL_Texture* TextureAsset::getTexture() const
{
    return m_texture;
}

TextureAsset::~TextureAsset()
{
    SDL_DestroyTexture(m_texture);
}