#pragma once

#include "IAsset.h"

#include <SDL_mixer.h>

class SFXAsset :
    public IAsset
{
public:
    SFXAsset();

    virtual void loadFromFile(const std::string& fpath) override;

    Mix_Chunk* getSFXChunk() const;

    ~SFXAsset();

private:
    Mix_Chunk* m_sfxChunk;
};

