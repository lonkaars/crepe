#pragma once

#include <string>

#include "../Component.h"

namespace crepe::api {

class Sprite : public Component {
public:
	Sprite(std::string path);

	std::string path;
};

} // namespace crepe::api
