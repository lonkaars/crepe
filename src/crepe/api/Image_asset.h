#pragma once



#include "Resource.h"
#include <string>

namespace crepe::api {


class Texture : public Resource {

public:
	Texture(const std::string&);
	~Texture();
};

}
