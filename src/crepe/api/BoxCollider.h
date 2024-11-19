#pragma once

#include "Vector2.h"
#include "../Collider.h"

namespace crepe {

/**
 * \brief A class representing a box-shaped collider.
 * 
 * This class is used for collision detection with other colliders (e.g., CircleCollider).
 */
class BoxCollider : public Collider {
public:
	BoxCollider(game_object_id_t game_object_id,Vector2 offset, double width, double height);

	//! Width of box collider 
	double width;

	//! Height of box collider
	double height;
};

} // namespace crepe
