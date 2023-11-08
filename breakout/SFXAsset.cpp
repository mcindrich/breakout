#include "SFXAsset.h"

#include <stdexcept>

SFXAsset::SFXAsset() : m_sfxChunk(nullptr)
{
}

void SFXAsset::loadFromFile(const std::string& fpath)
{
	m_sfxChunk = Mix_LoadWAV(fpath.c_str());
	if (!m_sfxChunk) {
		throw std::runtime_error("Unable to load SFX " + fpath);
	}
}

Mix_Chunk* SFXAsset::getSFXChunk() const
{
	return m_sfxChunk;
}

SFXAsset::~SFXAsset()
{
	Mix_FreeChunk(m_sfxChunk);
}
