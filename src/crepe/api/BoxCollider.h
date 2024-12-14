#pragma once

#include "../Collider.h"
#include "Vector2.h"
#include "types.h"

namespace crepe {

/**
 * \brief A class representing a box-shaped collider.
 *
 * This class is used for collision detection with other colliders (e.g., CircleCollider).
 */
class BoxCollider : public Collider {
public:
	BoxCollider(game_object_id_t game_object_id, const vec2 & dimensions,const vec2 & offset= {0,0});

	//! Width and height of the box collider
	vec2 dimensions;
};

} // namespace crepe
