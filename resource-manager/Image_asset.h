#pragma once



#include "resource.h"
#include <SDL_surface.h>





class Image : public Resource {

public:
	SDL_Surface* surface = nullptr;

	~Image();

};
