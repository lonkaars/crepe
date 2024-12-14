#pragma once

#include "Vector2.h"

#include "../Collider.h"

namespace crepe {

/**
 * \brief A class representing a circle-shaped collider.
 *
 * This class is used for collision detection with other colliders (e.g., BoxCollider).
 */
class CircleCollider : public Collider {
public:
	CircleCollider(game_object_id_t game_object_id, float radius, const vec2 & offset= {0,0});

	//! Radius of the circle collider.
	float radius;
};

} // namespace crepe
