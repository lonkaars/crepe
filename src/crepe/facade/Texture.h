#pragma once

#include "api/Resource.h"
#include <SDL2/SDL_render.h>
#include <memory>


namespace crepe {

class Texture {

public:
	Texture(const char * src);
	Texture(std::unique_ptr<api::Resource> res);
	~Texture();

private:
	void load(std::unique_ptr<api::Resource> res);

private:
	SDL_Texture* m_texture;
};

} // namespace crepe

