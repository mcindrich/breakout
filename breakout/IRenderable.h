#pragma once

#include <glm/glm.hpp>
#include "TextureAsset.h"

class IRenderable
{
public:
	IRenderable() = default;

	// allow overriding for different rendering
	virtual void render(SDL_Renderer* renderer) = 0;

	virtual ~IRenderable() = default;
};

