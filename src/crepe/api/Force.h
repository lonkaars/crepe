#pragma once

#include <cstdint>

#include "../Component.h"

namespace crepe {

class Force : public Component {
public:
	Force(game_object_id_t id, uint32_t magnitude, uint32_t direction);

	int32_t force_x;
	int32_t force_y;
};

} // namespace crepe
