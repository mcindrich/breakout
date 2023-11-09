#pragma once

#include "IRenderableTexture.h"
#include "MovableObject2D.h"

class MovableTexture2D
	:
	public MovableObject2D,
	public IRenderableTexture
{
public:
	MovableTexture2D(TextureAsset& texture);

	// default rendering
	virtual void render(SDL_Renderer* renderer) override;
};

