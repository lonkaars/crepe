#pragma once

#include "Component.h"
#include <cstdint>

namespace crepe {

enum class BodyType {
    Static,     // Does not move (e.g. walls, ground ...)
    Dynamic,    // Moves and responds to forces (e.g. player, physics objects ...)
    Kinematic   // Moves but does not respond to forces (e.g. moving platforms ...)
};

class Rigidbody : public Component {
public:
	Rigidbody(uint32_t gameObjectId,int mass, int gravityScale, BodyType bodyType);
	int32_t velocity_x;
    int32_t velocity_y;
	int mass;
	int gravity_scale;
	BodyType body_type;
};

} // namespace crepe::api
