#pragma once

#include <string>

#include "Component.h"

namespace crepe {

class Sprite : public Component {
public:
	Sprite(uint32_t gameObjectId,std::string path);

	std::string path;
};

} // namespace crepe
