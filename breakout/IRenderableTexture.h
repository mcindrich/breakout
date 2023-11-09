#pragma once

#include "IRenderable.h"
#include "TextureAsset.h"

class IRenderableTexture :
    public IRenderable
{
public:
    IRenderableTexture(TextureAsset& texture);

protected:
    TextureAsset& getTextureAsset();

private:
    TextureAsset& m_texture;
};

