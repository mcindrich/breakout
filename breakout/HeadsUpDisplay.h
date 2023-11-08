#pragma once

#include "IRenderObject.h"
#include "FontAsset.h"

#include <glm/glm.hpp>

class HeadsUpDisplay :
    public IRenderObject
{
public:
    HeadsUpDisplay(unsigned int &lives_ref, unsigned int &points_ref, unsigned int &level_ref, glm::vec2 window_size);

    void setFont(FontAsset& font_asset);

    virtual void render(SDL_Renderer* renderer) override;

private:
    unsigned int& m_livesRef;
    unsigned int& m_pointsRef;
    unsigned int& m_levelRef;

    TTF_Font* m_font;
};

