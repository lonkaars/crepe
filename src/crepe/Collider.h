#pragma once

#include "Component.h"
#include "types.h"

namespace crepe {

/**
 * \brief Base collider class
 */
class Collider : public Component {
public:
	Collider(game_object_id_t id, const vec2 & offset);

public:
	/**
	* \brief Offset of the collider relative to the rigidbody position.
	*
	* The `offset` defines the positional shift applied to the collider relative to the position of the rigidbody it is attached to.
	* This allows the collider to be placed at a different position than the rigidbody.
	*
	*/
	vec2 offset;
};

} // namespace crepe
