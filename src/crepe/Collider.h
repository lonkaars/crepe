#pragma once

#include "Component.h"

namespace crepe {

class Collider : public Component {
public:
	Collider(uint32_t game_object_id);

	int size;
};

} // namespace crepe
