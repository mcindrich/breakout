#pragma once

#include "IAsset.h"

#include <SDL_ttf.h>

class FontAsset :
	public IAsset
{
public:
	FontAsset(unsigned int size);

	virtual void loadFromFile(const std::string& fpath) override;

	unsigned int getFontSize() const;
	TTF_Font* getFont() const;

	~FontAsset();

private:
	unsigned int m_fontSize;
	TTF_Font* m_font;

};

