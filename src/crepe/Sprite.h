#pragma once

#include <string>

#include "Component.h"

namespace crepe {

class Sprite : public Component {
public:
	Sprite(std::string path);

	std::string path;
};

} // namespace crepe
