#include <cmath>

#include "Force.h"

namespace crepe {

Force::Force(game_object_id_t id, uint32_t magnitude, uint32_t direction) : Component(id) {
	// TODO: A standard angle unit should be established for the entire engine
	// and assumed to be the default everywhere. Only conversion functions should
	// explicitly contain the unit (i.e. `deg_to_rad()` & `rad_to_deg()`)

	// Convert direction from degrees to radians
	float radian_direction = static_cast<float>(direction) * (M_PI / 180.0f);
	force_x = static_cast<int32_t>(
		std::round(magnitude * std::cos(radian_direction)));
	force_y = static_cast<int32_t>(
		std::round(magnitude * std::sin(radian_direction)));
}

} // namespace crepe
