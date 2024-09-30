#pragma once



#include "resource.h"
#include "constants.h"
#include <SDL_render.h>
#include <string>



using namespace crepe;


class ResourceFactory {

public:

	template<typename T>
	static Resource* create_resource(const Constants::FILE_PATH& file_path){
		
		return new T(convert_file_to_string(file_path));
	}

private:
	static std::string convert_file_to_string(const std::string& path);

};




