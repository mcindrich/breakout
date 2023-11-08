#pragma once

#include <SDL_render.h>
#include <glm/glm.hpp>

class IRenderObject
{
public:
	IRenderObject();

	// allow overriding for different rendering
	virtual void render(SDL_Renderer* renderer);

	glm::vec2 getPosition() const;
	glm::vec2 getSize() const;

	~IRenderObject();

protected:
	void setTexture(SDL_Texture* texture);
	SDL_Texture* getTexture();

	void setPosition(glm::vec2 position);
	void setSize(glm::vec2 size);

private:
	glm::vec2 m_position;
	glm::vec2 m_size;
	SDL_Texture* m_texture;
};

