#pragma once

#include "SDL_rect.h"
#include "api/baseResource.h"
#include "api/Resource.h"
#include <SDL2/SDL_render.h>
#include <memory>

namespace crepe {



class Texture  : public api::BaseResource{

public:
	Texture(const char * src);
	Texture(std::unique_ptr<api::Resource> res);
	~Texture();

	SDL_Texture* get_texture() const;
	SDL_Rect& get_rect() ;
private:
	void load(std::unique_ptr<api::Resource> res);

private:
	SDL_Texture* m_texture;
	SDL_Rect srcrect;
};

} // namespace crepe

