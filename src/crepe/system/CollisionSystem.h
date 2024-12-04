#pragma once

#include <optional>
#include <variant>
#include <vector>

#include "api/BoxCollider.h"
#include "api/CircleCollider.h"
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
	//! A variant type that can hold either a BoxCollider or a CircleCollider.
	using collider_variant = std::variant<std::reference_wrapper<BoxCollider>,
										  std::reference_wrapper<CircleCollider>>;

	//! Enum representing the types of collider pairs for collision detection.
	enum class CollisionInternalType {
		BOX_BOX,
		CIRCLE_CIRCLE,
		BOX_CIRCLE,
		CIRCLE_BOX,
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
		Transform & transform;
		Rigidbody & rigidbody;
	};

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
	struct CollisionInfo {
		Collider & this_collider;
		Transform & this_transform;
		Rigidbody & this_rigidbody;
		Metadata & this_metadata;
		Collider & other_collider;
		Transform & other_transform;
		Rigidbody & other_rigidbody;
		Metadata & other_metadata;
		//! The resolution vector for the collision.
		vec2 resolution;
		//! The direction of movement for resolving the collision.
		Direction resolution_direction = Direction::NONE;
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
	CollisionInternalType get_collider_type(const collider_variant & collider1,
											const collider_variant & collider2) const;

	/**
		* \brief Calculates the current position of a collider.
		* 
		* Combines the Collider offset, Transform position, and Rigidbody offset to compute the position of the collider.
		* 
		* \param collider_offset The offset of the collider.
		* \param transform The Transform of the associated game object.
		* \param rigidbody The Rigidbody of the associated game object.
		* \return The calculated position of the collider.
		*/
	vec2 get_current_position(const vec2 & collider_offset, const Transform & transform,
							  const Rigidbody & rigidbody) const;

private:
	/**
		* \brief Handles collision resolution between two colliders.
		* 
		* Processes collision data and adjusts objects to resolve collisions and/or calls the user oncollision script function.
		* 
		* \param data1 Collision data for the first collider.
		* \param data2 Collision data for the second collider.
		*/
	void collision_handler_request(CollisionInternal & data1, CollisionInternal & data2);

	/**
		* \brief Resolves collision between two colliders and calculates the movement required.
		* 
		* Determines the displacement and direction needed to separate colliders based on their types.
		* 
		* \param data1 Collision data for the first collider.
		* \param data2 Collision data for the second collider.
		* \param type The type of collider pair.
		* \return A pair containing the resolution vector and direction for the first collider.
		*/
	std::pair<vec2, Direction> collision_handler(CollisionInternal & data1,
												 CollisionInternal & data2,
												 CollisionInternalType type);

	/**
		* \brief Calculates the resolution vector for two BoxColliders.
		* 
		* Computes the displacement required to separate two overlapping BoxColliders.
		* 
		* \param box_collider1 The first BoxCollider.
		* \param box_collider2 The second BoxCollider.
		* \param position1 The position of the first BoxCollider.
		* \param position2 The position of the second BoxCollider.
		* \return The resolution vector for the collision.
		*/
	vec2 get_box_box_resolution(const BoxCollider & box_collider1,
								const BoxCollider & box_collider2, const vec2 & position1,
								const vec2 & position2) const;

	/**
		* \brief Calculates the resolution vector for two CircleCollider.
		* 
		* Computes the displacement required to separate two overlapping CircleCollider.
		* 
		* \param circle_collider1 The first CircleCollider.
		* \param circle_collider2 The second CircleCollider.
		* \param position1 The position of the first CircleCollider.
		* \param position2 The position of the second CircleCollider.
		* \return The resolution vector for the collision.
		*/
	vec2 get_circle_circle_resolution(const CircleCollider & circle_collider1,
									  const CircleCollider & circle_collider2,
									  const vec2 & final_position1,
									  const vec2 & final_position2) const;

	/**
		* \brief Calculates the resolution vector for two CircleCollider.
		* 
		* Computes the displacement required to separate two overlapping CircleCollider.
		* 
		* \param circle_collider The first CircleCollider.
		* \param box_collider The second CircleCollider.
		* \param circle_position The position of the CircleCollider.
		* \param box_position The position of the BocCollider.
		* \return The resolution vector for the collision.
		*/
	vec2 get_circle_box_resolution(const CircleCollider & circle_collider,
								   const BoxCollider & box_collider,
								   const vec2 & circle_position,
								   const vec2 & box_position) const;

	/**
		* \brief Determines the appropriate collision handler for a collision.
		* 
		* Decides the correct resolution process based on the dynamic or static nature of the colliders involved.
		* 
		* \param info Collision information containing data about both colliders.
		*/
	void determine_collision_handler(CollisionInfo & info);

	/**
		* \brief Handles collisions involving static objects.
		* 
		* Resolves collisions by adjusting positions and modifying velocities if bounce is enabled.
		* 
		* \param info Collision information containing data about both colliders.
		*/
	void static_collision_handler(CollisionInfo & info);

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
	gather_collisions(std::vector<CollisionInternal> & colliders);

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
	bool get_collision(const CollisionInternal & first_info,
					   const CollisionInternal & second_info,
					   CollisionInternalType type) const;

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
	bool get_box_box_collision(const BoxCollider & box1, const BoxCollider & box2,
							   const Transform & transform1, const Transform & transform2,
							   const Rigidbody & rigidbody1,
							   const Rigidbody & rigidbody2) const;

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
	bool get_box_circle_collision(const BoxCollider & box1, const CircleCollider & circle2,
								  const Transform & transform1, const Transform & transform2,
								  const Rigidbody & rigidbody1,
								  const Rigidbody & rigidbody2) const;

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
	bool get_circle_circle_collision(const CircleCollider & circle1,
									 const CircleCollider & circle2,
									 const Transform & transform1,
									 const Transform & transform2,
									 const Rigidbody & rigidbody1,
									 const Rigidbody & rigidbody2) const;
};

} // namespace crepe
