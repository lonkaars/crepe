

#include <filesystem>
#include <string>

#include "resource_fabricator.h"
#include "resource.h"
#include "Image_asset.h"
#include "Audio_asset.h"

#include <SDL2/SDL_image.h>


Resource* ResourceFactory::create_resource(const Constants::FILE_PATH &file_path){

	std::string extension = std::filesystem::path(file_path).extension();



	if( extension == Constants::PNG_EXT ) {
		Image* img = new Image;
		img->surface = IMG_Load(file_path.c_str());
		return img;
	}
	else if ( extension == Constants::OGG_EXT ){
		return new Audio;
	}

	return nullptr;
}
