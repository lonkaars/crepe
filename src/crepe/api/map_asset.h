#pragma once

#include "Resource.h"
#include <string>


using namespace crepe::api;

class Map : public Resource {

public:
	Map(const std::string& );
	~Map();
};
