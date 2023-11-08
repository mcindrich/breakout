#pragma once

#include "IAsset.h"

#include <SDL_image.h>

class ImageAsset :
    public IAsset
{
public:
    ImageAsset();

    virtual void loadFromFile(const std::string& fpath) override;

    SDL_Surface* getSurface() const;

    ~ImageAsset();

private:
    SDL_Surface* m_surface;
};

