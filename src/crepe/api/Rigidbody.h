#pragma once

#include <cstdint>

#include "../Component.h"

namespace crepe {

// FIXME: can't this enum be defined inside the class declaration of Rigidbody?
enum class BodyType {
	//! Does not move (e.g. walls, ground ...)
	STATIC,
	//! Moves and responds to forces (e.g. player, physics objects ...)
	DYNAMIC,
	//! Moves but does not respond to forces (e.g. moving platforms ...)
	KINEMATIC,
};

class Rigidbody : public Component {
public:
	Rigidbody(uint32_t game_object_id, int mass, int gravity_scale,
			  BodyType body_type);
	int32_t velocity_x;
	int32_t velocity_y;
	int mass;
	int gravity_scale;
	BodyType body_type;
};

} // namespace crepe
