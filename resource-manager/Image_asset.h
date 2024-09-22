#pragma once



#include "resource.h"
#include "spritesheet.h"
#include <SDL_surface.h>
#include <string>





class Image : public Resource {

public:
	Image(const std::string& path);
	~Image();

	SDL_Surface* getSurface() const;

private:
	SDL_Surface* surface;
};

