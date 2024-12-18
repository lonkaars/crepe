#pragma once

#include <optional>
#include <variant>
#include <vector>

#include "api/BoxCollider.h"
#include "api/CircleCollider.h"
#include "api/Event.h"
#include "api/Metadata.h"
#include "api/Rigidbody.h"
#include "api/Transform.h"
#include "api/Vector2.h"

#include "Collider.h"
#include "System.h"

namespace crepe {

//! A system responsible for detecting and handling collisions between colliders.
class CollisionSystem : public System {
public:
	using System::System;
private:
	//! Enum representing movement directions during collision resolution.
	enum class Direction {
		//! No movement required.
		NONE,
		//! Movement in the X direction.
		X_DIRECTION,
		//! Movement in the Y direction.
		Y_DIRECTION,
		//! Movement in both X and Y directions.
		BOTH
	};
public:
	/**
		* \brief Structure representing detailed collision information between two colliders.
		*
		* Includes information about the colliding objects and the resolution data for handling the collision.
		*/

	struct ColliderInfo {
  Transform & transform;
  Rigidbody & rigidbody;
  Metadata & metadata;
	};

	struct CollisionInfo {
		ColliderInfo self;
		ColliderInfo other;
		//! The resolution vector for the collision.
		vec2 resolution;
		//! The direction of movement for resolving the collision.
		Direction resolution_direction = Direction::NONE;
		CollisionInfo operator - () const;
	};

private:
	//! A variant type that can hold either a BoxCollider or a CircleCollider.
	using collider_variant = std::variant<std::reference_wrapper<BoxCollider>,
										  std::reference_wrapper<CircleCollider>>;

	//! Enum representing the types of collider pairs for collision detection.
	enum class CollisionInternalType {
		BOX_BOX,
		CIRCLE_CIRCLE,
		BOX_CIRCLE,
		CIRCLE_BOX,
		NONE,
	};

	/**
		* \brief A structure to store the collision data of a single collider.
		*
		* This structure all components and id that are for needed within this system when calculating or handeling collisions.
		* The transform and rigidbody are mostly needed for location and rotation.
		* In rigidbody additional info is written about what the body of the object is,
		* and how it should respond on a collision.
		*/
	struct CollisionInternal {
		game_object_id_t id = 0;
		collider_variant collider;
		ColliderInfo info;
		vec2 resolution;
		Direction resolution_direction = Direction::NONE;
	};

	struct BoxColliderInternal {
		BoxCollider & collider;
		Transform & transform;
		Rigidbody & rigidbody;
	};

	struct CircleColliderInternal {
		CircleCollider & collider;
		Transform & transform;
		Rigidbody & rigidbody;
	};

public:
	//! Updates the collision system by checking for collisions between colliders and handling them.
	void update() override;

private:
	/**
		* \brief Determines the type of collider pair from two colliders.
		*
		* Uses std::holds_alternative to identify the types of the provided colliders.
		*
		* \param collider1 First collider variant (BoxCollider or CircleCollider).
		* \param collider2 Second collider variant (BoxCollider or CircleCollider).
		* \return The combined type of the two colliders.
		*/
	CollisionInternalType get_collider_type(const collider_variant & collider1, const collider_variant & collider2) const;

private:
	/**
		* \brief Handles collision resolution between two colliders.
		*
		* Processes collision data and adjusts objects to resolve collisions and/or calls the user oncollision script function.
		*
		* \param data1 Collision data for the first collider.
		* \param data2 Collision data for the second collider.
		*/
	CollisionInfo get_collision_info(const CollisionInternal & this_data, const CollisionInternal & other_data) const; //done


	Direction resolution_correction(vec2 & resolution,const Rigidbody::Data & rigidbody);


	/**
		* \brief Determines the appropriate collision handler for a collision.
		*
		* Decides the correct resolution process based on the dynamic or static nature of the colliders involved.
		*
		* \param info Collision information containing data about both colliders.
		*/
	void determine_collision_handler(const CollisionInfo & info); //done

	/**
		* \brief Calls both collision script
		*
		* Calls both collision script to let user add additonal handeling or handle full collision.
		*
		* \param info Collision information containing data about both colliders.
		*/
	void call_collision_events(const CollisionInfo & info, const CollisionInfo & info_inverted);

	/**
		* \brief Handles collisions involving static objects.
		*
		* Resolves collisions by adjusting positions and modifying velocities if bounce is enabled.
		*
		* \param info Collision information containing data about both colliders.
		*/
	void static_collision_handler(const CollisionInfo & info); //done

	/**
		* \brief Handles collisions involving dynamic objects.
		*
		* Resolves collisions by adjusting positions and modifying velocities if bounce is enabled.
		*
		* \param info Collision information containing data about both colliders.
		*/
	void dynamic_collision_handler(const CollisionInfo & info); //done

private:
	/**
		* \brief Checks for collisions between colliders.
		*
		* Identifies collisions and generates pairs of colliding objects for further processing.
		*
		* \param colliders A collection of all active colliders.
		* \return A list of collision pairs with their associated data.
		*/
	std::vector<std::pair<CollisionInternal, CollisionInternal>>
	gather_collisions(std::vector<CollisionInternal> & colliders); //done

	/**
	 * \brief Checks if the settings allow collision
	 *
	 * This function checks if there is any collison layer where each object is located in.
	 * After checking the layers it checks the names and at last the tags.
	 * if in all three sets nothing is found collision can not happen.
	 *
	 * \param this_rigidbody Rigidbody of first object
	 * \param other_rigidbody Rigidbody of second collider
	 * \param this_metadata Rigidbody of first object
	 * \param other_metadata Rigidbody of second object
	 * \return Returns true if there is at least one comparision found.
	 */
	bool should_collide(const CollisionInternal & self, const CollisionInternal & other) const; //done

	/**
		* \brief Checks for collision between two colliders.
		*
		* Calls the appropriate collision detection function based on the collider types.
		*
		* \param first_info Collision data for the first collider.
		* \param second_info Collision data for the second collider.
		* \param type The type of collider pair.
		* \return True if a collision is detected, otherwise false.
		*/
	bool detect_collision(CollisionInternal & first_info, CollisionInternal & second_info, const CollisionInternalType & type);

	/**
		* \brief Detects collisions between two BoxColliders.
		*
		* \param box1 The first BoxCollider.
		* \param box2 The second BoxCollider.
		* \param transform1 Transform of the first object.
		* \param transform2 Transform of the second object.
		* \param rigidbody1 Rigidbody of the first object.
		* \param rigidbody2 Rigidbody of the second object.
		* \return True if a collision is detected, otherwise false.
		*/
	vec2 get_box_box_detection(const BoxColliderInternal & box1, const BoxColliderInternal & box2) const;

	/**
	 * \brief Check collision for box on circle collider
	 *
	 * \param box1 The BoxCollider
	 * \param circle2 The CircleCollider
	 * \param transform1 Transform of the first object.
	 * \param transform2 Transform of the second object.
	 * \param rigidbody1 Rigidbody of the first object.
	 * \param rigidbody2 Rigidbody of the second object.
	 * \return True if a collision is detected, otherwise false.
	 */
	vec2 get_box_circle_detection(const BoxColliderInternal & box1, const CircleColliderInternal & circle2) const;

	/**
	 * \brief Check collision for circle on circle collider
	 *
	 * \param circle1 First CircleCollider
	 * \param circle2 Second CircleCollider
	 * \param transform1 Transform of the first object.
	 * \param transform2 Transform of the second object.
	 * \param rigidbody1 Rigidbody of the first object.
	 * \param rigidbody2 Rigidbody of the second object.
	 * \return True if a collision is detected, otherwise false.
	 *
	 * \return status of collision
	 */
	vec2 get_circle_circle_detection(const CircleColliderInternal & circle1, const CircleColliderInternal & circle2) const;
};

/**
 * \brief Event triggered during a collision between objects.
 */
class CollisionEvent : public Event {
public:
	crepe::CollisionSystem::CollisionInfo info;
	CollisionEvent(const crepe::CollisionSystem::CollisionInfo & collisionInfo)
		: info(collisionInfo) {}
};

} // namespace crepe
