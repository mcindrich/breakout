#pragma once

#include "IRenderable.h"
#include "AssetManager.h"
#include "Text.h"

#include <glm/glm.hpp>

class HeadsUpDisplay :
    public IRenderable
{
public:
    HeadsUpDisplay(FontAsset &font, unsigned int &lives_ref, unsigned int &points_ref, unsigned int &level_ref, glm::vec2 window_size);

    virtual void render(SDL_Renderer* renderer) override;

private:
    void renderLivesText(SDL_Renderer* renderer);
    void renderPointsText(SDL_Renderer* renderer);
    void renderLevelText(SDL_Renderer* renderer);

    unsigned int& m_livesRef;
    unsigned int& m_pointsRef;
    unsigned int& m_levelRef;

    Text m_livesText;
    Text m_pointsText;
    Text m_levelText;
};

