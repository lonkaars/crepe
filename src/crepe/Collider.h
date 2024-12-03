#pragma once

#include "Component.h"
#include "types.h"

namespace crepe {

class Collider : public Component {
public:
	Collider(game_object_id_t id, const vec2& offset);

public:
	/**
	* \brief Offset of the collider relative to the rigidbody position.
	*
	* The `offset` defines the positional shift applied to the collider relative to the position of the rigidbody it is attached to.
	* This allows the collider to be placed at a different position than the rigidbody, which can be useful for scenarios
	* where the collider's position needs to differ from the rigidbody's center, such as in non-centered colliders.
	* 
	* - The `offset` is typically used when the collider is not meant to be centered exactly on the rigidbody's position.
	* - For example, the collider might need to be shifted to account for an object with an asymmetrical shape or for objects
	*   where the pivot point of the rigidbody is different from the collider's center.
	* 
	* When multiple colliders are added to the same object (e.g., a character with separate body parts or a vehicle with multiple zones),
	* the offset is important for properly positioning each collider relative to the rigidbody, allowing accurate collision detection.
	* 
	* - Multiple colliders can be used on the same object, and each can have its own unique offset.
	* - Overlap between colliders is allowed and does not impact performance.
	*/
	vec2 offset;
};

} // namespace crepe
