#pragma once



#include "Image_asset.h"
#include "map_asset.h"
#include "tiledMap.h"

#include <SDL_surface.h>

class ResourceConverter{

	
public:
	ResourceConverter();
	~ResourceConverter();

	SDL_Surface* FromStringToImage(const Texture&);
	TiledMap FromStringToMap(const Map&);

	//TODO:
	//convertrs a string map into a real map:

};
