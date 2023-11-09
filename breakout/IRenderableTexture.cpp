#include "IRenderableTexture.h"

IRenderableTexture::IRenderableTexture(TextureAsset& texture) : m_texture(texture)
{
}

TextureAsset& IRenderableTexture::getTextureAsset()
{
    return m_texture;
}
