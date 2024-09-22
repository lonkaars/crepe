

#include "Image_asset.h"
#include "spritesheet.h"
#include <SDL2/SDL_surface.h>
#include <SDL_image.h>
#include <string>


Image::Image(const std::string& path){
	surface = IMG_Load(path.c_str());
}


Image::~Image(){
	SDL_FreeSurface(surface);
}

SDL_Surface* Image::getSurface() const {
	return surface;
}
