#pragma once

#include <SDL_render.h>

class IRenderObject
{
public:
	virtual void render(SDL_Renderer* renderer) = 0;

protected:
	void setTexture(SDL_Texture* texture);
	SDL_Texture* getTexture();

private:
	SDL_Texture* m_texture;
};

