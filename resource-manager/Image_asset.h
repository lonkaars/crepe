#pragma once



#include "resource.h"
#include <SDL_render.h>
#include <SDL_surface.h>
#include <string>





class Texture : public Resource {

public:
	Texture(const std::string& path);
	~Texture();
	
	void setTexture(SDL_Renderer& renderer);		
	SDL_Surface* getSurface() const;
	SDL_Texture* getTexture() const;

private:
	SDL_Surface* m_surface;
	SDL_Texture* m_texture;
};

