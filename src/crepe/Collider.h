#pragma once

#include "api/Vector2.h"

#include "Component.h"

namespace crepe {

class Collider : public Component {
public:
	Collider(game_object_id_t id, Vector2 offset);

public:
	//! Offset of the collider relative to rigidbody position 
	Vector2 offset;
};

} // namespace crepe
