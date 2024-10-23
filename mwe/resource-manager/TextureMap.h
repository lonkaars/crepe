#pragma once

#include <SDL_rect.h>
#include <SDL_render.h>
#include <string>

class TextureMap final {
public:
	TextureMap();
	~TextureMap();

	TextureMap(const TextureMap &) = delete;
	TextureMap(TextureMap &&) = delete;

	TextureMap & operator=(const TextureMap &) = delete;
	TextureMap & operator=(TextureMap &&) = delete;

	bool loadFromFile(const std::string &, SDL_Renderer *);
	SDL_Point getSize() const { return m_size; }

	operator SDL_Texture *() { return m_texture; }

private:
	SDL_Texture * m_texture;
	SDL_Point m_size;
};
