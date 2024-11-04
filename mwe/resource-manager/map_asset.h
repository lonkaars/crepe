#pragma once

#include "resource.h"
#include <string>

class Map : public Resource {

public:
	Map(const std::string &);
	~Map();
};
