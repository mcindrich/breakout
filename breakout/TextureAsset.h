#pragma once

#include "IAsset.h"

#include <SDL_render.h>

class TextureAsset :
    public IAsset
{
public:
    TextureAsset(SDL_Renderer *renderer);

    virtual void loadFromFile(const std::string& fpath) override;

    SDL_Texture* getTexture() const;

    ~TextureAsset();

private:
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;
};

