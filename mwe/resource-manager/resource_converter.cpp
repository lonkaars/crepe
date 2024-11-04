

#include "resource_converter.h"
#include "Image_asset.h"
#include "map_asset.h"
#include "resource.h"
#include <SDL_image.h>
#include <SDL_surface.h>
#include <iostream>
#include <string>

ResourceConverter::ResourceConverter() { IMG_Init(IMG_INIT_PNG); }

ResourceConverter::~ResourceConverter() { IMG_Quit(); }

SDL_Surface * ResourceConverter::FromStringToImage(const Texture & resource) {
	const std::string & content = resource.getContent();
	SDL_RWops * rw = SDL_RWFromConstMem(content.data(), content.size());
	if (!rw) {
		std::cerr << "Failed to create SDL_RWops: " << SDL_GetError()
				  << std::endl;
		return nullptr;
	}

	SDL_Surface * surface = IMG_Load_RW(rw, 1);
	if (!surface) {
		std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
	}
	return surface;
}

TiledMap ResourceConverter::FromStringToMap(const Map & resource) {
	const std::string & content = resource.getContent();
	return TiledMap(content);
}
