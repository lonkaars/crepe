

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
		return new Image(file_path);
	}
	else if ( extension == Constants::OGG_EXT ){
		return new Audio;
	}

	return nullptr;
}
