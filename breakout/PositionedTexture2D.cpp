#include "PositionedTexture2D.h"

PositionedTexture2D::PositionedTexture2D(TextureAsset& texture) : IRenderableTexture(texture)
{
}

void PositionedTexture2D::render(SDL_Renderer* renderer)
{
	// render on position
	SDL_FRect rect;

	rect = { getPosition().x, getPosition().y, getSize().x, getSize().y };

	SDL_RenderCopyF(renderer, getTextureAsset().getTexture(), NULL, &rect);
}
