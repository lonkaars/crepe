

#include "Image_asset.h"
#include <SDL2/SDL_surface.h>



Image::~Image(){
	if (surface) {
		SDL_FreeSurface(surface);
	}
}
