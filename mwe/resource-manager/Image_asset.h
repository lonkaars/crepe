#pragma once

#include "resource.h"
#include <string>

class Texture : public Resource {

public:
	Texture(const std::string &);
	~Texture();
};
