#pragma once

#include <cstdint>

#include "../Component.h"

namespace crepe {

class Force : public Component {
public:
	Force(uint32_t game_object_id, uint32_t magnitude, uint32_t direction);

	int32_t force_x;
	int32_t force_y;
};

} // namespace crepe
