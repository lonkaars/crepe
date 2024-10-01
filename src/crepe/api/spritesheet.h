#pragma once




#include "Resource.h"
#include <string>


namespace crepe::api {



class SpriteSheet : public Resource{

public:
	SpriteSheet(const std::string&);
	~SpriteSheet();

};
}
