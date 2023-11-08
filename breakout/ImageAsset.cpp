#include "ImageAsset.h"

#include <stdexcept>

ImageAsset::ImageAsset() : m_surface(nullptr)
{
}

void ImageAsset::loadFromFile(const std::string& fpath)
{
	m_surface = IMG_Load(fpath.c_str());
	if (!m_surface) {
		throw std::runtime_error("Unable to load image " + fpath);
	}
}

SDL_Surface* ImageAsset::getSurface() const
{
	return m_surface;
}

ImageAsset::~ImageAsset()
{
	SDL_FreeSurface(m_surface);
}
