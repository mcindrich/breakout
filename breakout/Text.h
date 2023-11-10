#pragma once

#include "IRenderable.h"
#include "PositionedObject2D.h"
#include "FontAsset.h"

class Text :
    public PositionedObject2D,
    public IRenderable
{
public:
    Text(FontAsset& font);

    void setText(const std::string& text);
    void setColor(const SDL_Color &color);

    virtual void render(SDL_Renderer* renderer) override;

private:
    std::string m_text;
    SDL_Color m_color;
    FontAsset& m_font;
};