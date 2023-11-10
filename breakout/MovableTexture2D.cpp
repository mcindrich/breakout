#include "MovableTexture2D.h"

MovableTexture2D::MovableTexture2D(TextureAsset& texture) : IRenderableTexture(texture)
{
}

void MovableTexture2D::render(SDL_Renderer* renderer)
{
	// render on position
	SDL_FRect rect;

	rect = { getTopLeftPosition().x, getTopLeftPosition().y, getSize().x, getSize().y };

	SDL_RenderCopyF(renderer, getTextureAsset().getTexture(), NULL, &rect);
}
