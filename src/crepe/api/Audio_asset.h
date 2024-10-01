#pragma once


#include "resource.h"
#include <string>


namespace crepe::api {


class Audio : public Resource {

public:
	Audio(const std::string&);
	~Audio();

};
}
