#pragma once



#include "Audio_asset.h"
#include "Image_asset.h"
#include "resource.h"
#include "constants.h"
#include "spritesheet.h"
#include <SDL_render.h>



using namespace crepe;


class ResourceFactory {

public:

	template<typename T>
	static Resource* create_resource(const Constants::FILE_PATH& file_path){
		return new T(file_path);
	}

};




