#include <cmath>

#include "Force.h"

namespace crepe::api {

Force::Force(uint32_t game_object_id, uint32_t magnitude, uint32_t direction)
	: Component(game_object_id) {
	// Convert direction from degrees to radians
	float radian_direction = static_cast<float>(direction) * (M_PI / 180.0f);
	force_x = static_cast<int32_t>(
		std::round(magnitude * std::cos(radian_direction)));
	force_y = static_cast<int32_t>(
		std::round(magnitude * std::sin(radian_direction)));
}

} // namespace crepe::api
