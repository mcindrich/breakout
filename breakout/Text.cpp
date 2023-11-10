#include "Text.h"

#include <SDL_image.h>

#include <iostream>

Text::Text(FontAsset& font) : m_font(font), m_color(SDL_Color{255, 255, 255})
{
}

void Text::setText(const std::string& text)
{
	m_text = text;
}

void Text::setColor(const SDL_Color& color)
{
	m_color = color;
}

// Could be optimized to changing texture on text change
void Text::render(SDL_Renderer* renderer)
{
	// create a surface and texture from font and text
	auto surface = TTF_RenderText_Solid(m_font.getFont(), m_text.c_str(), m_color);
	auto texture = SDL_CreateTextureFromSurface(renderer, surface);

	// render texture at setup position

	SDL_FRect rect = { getPosition().x, getPosition().y, getSize().x, getSize().y};

	SDL_RenderCopyF(renderer, texture, NULL, &rect);

	// free created surface and texture each iteration
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}
