#pragma once

#include "api/Vector2.h"

#include "Component.h"

namespace crepe {

class Collider : public Component {
public:
	Collider(game_object_id_t id, Vector2 offset);

protected:
    // Friend class allowing access to copy constructor
    friend class CollisionSystem;

    // Copy Constructor (Restricted to CollisionSystem)
    Collider(const Collider &other)
        : Component(other.game_object_id), offset(other.offset) {}

public:
	//! Offset of the collider relative to rigidbody position 
	Vector2 offset;
};

} // namespace crepe
