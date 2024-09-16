#pragma once



#include "resource.h"
#include "constants.h"


using namespace crepe;


class ResourceFactory {

public:

	static Resource* create_resource(const Constants::FILE_PATH& file_path);


};




