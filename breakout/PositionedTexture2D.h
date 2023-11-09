#pragma once

#include "IRenderableTexture.h"
#include "PositionedObject2D.h"

class PositionedTexture2D
	: 
	public PositionedObject2D,
	public IRenderableTexture
{
public:
	PositionedTexture2D(TextureAsset& texture);

	// default rendering
	virtual void render(SDL_Renderer* renderer) override;
};

