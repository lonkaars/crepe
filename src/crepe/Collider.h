#pragma once

#include "api/Vector2.h"

#include "Component.h"
#include "types.h"

namespace crepe {

class Collider : public Component {
public:
	Collider(game_object_id_t id, vec2 offset);

public:
	//! Offset of the collider relative to rigidbody position 
	vec2 offset;
};

} // namespace crepe
