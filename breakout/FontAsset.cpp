#include "FontAsset.h"

#include <stdexcept>

FontAsset::FontAsset(unsigned int size) : m_fontSize(size), m_font(nullptr)
{
}

void FontAsset::loadFromFile(const std::string& fpath)
{
	m_font = TTF_OpenFont(fpath.c_str(), m_fontSize);

	if (!m_font) {
		throw std::runtime_error("Unable to load font " + fpath);
	}
}

unsigned int FontAsset::getFontSize() const
{
	return m_fontSize;
}

TTF_Font* FontAsset::getFont() const
{
	return m_font;
}

FontAsset::~FontAsset()
{
	TTF_CloseFont(m_font);
}
