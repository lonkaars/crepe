#pragma once

#include <vector>
#include <variant>
#include <optional>

#include "api/Rigidbody.h"
#include "api/Transform.h"
#include "api/BoxCollider.h"
#include "api/CircleCollider.h"
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
	using collider_variant = std::variant<std::reference_wrapper<BoxCollider>, std::reference_wrapper<CircleCollider>>;

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
		* This structure stores the collider type, its associated transform, and its rigidbody.
		*/
	struct CollisionInternal {
		//! Store either BoxCollider or CircleCollider
		collider_variant& collider; 
		Transform& transform;
		Rigidbody& rigidbody;
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
	struct CollisionInfo{
    Collider& first_collider;
		Transform& first_transform;
		Rigidbody& first_rigidbody;
    Collider& second_collider;
		Transform& second_transform;
		Rigidbody& second_rigidbody;
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
	CollisionInternalType check_collider_type(const collider_variant& collider1,const collider_variant& collider2);

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
	vec2 current_position(vec2 collider_offset, const Transform& transform, const Rigidbody& rigidbody);

private:

	/**
		* \brief Handles collision resolution between two colliders.
		* 
		* Processes collision data and adjusts objects to resolve collisions and/or calls the user oncollision script function.
		* 
		* \param data1 Collision data for the first collider.
		* \param data2 Collision data for the second collider.
		*/
	void collision_handler_request(CollisionInternal& data1,CollisionInternal& data2);

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
	std::pair<vec2,Direction> collision_handler(CollisionInternal& data1,CollisionInternal& data2 ,CollisionInternalType type);

	/**
		* \brief Calculates the resolution vector for two BoxColliders.
		* 
		* Computes the displacement required to separate two overlapping BoxColliders.
		* 
		* \param box_collider1 The first BoxCollider.
		* \param box_collider2 The second BoxCollider.
		* \param position1 The position of the first BoxCollider.
		* \param position2 The position of the second BoxCollider.
		* \return The resolution vector for the first BoxCollider.
		*/
	vec2 box_box_resolution(const BoxCollider& box_collider1,const BoxCollider& box_collider2,vec2 position1,vec2 position2);

	/**
		* \brief Determines the appropriate collision handler for a collision.
		* 
		* Decides the correct resolution process based on the dynamic or static nature of the colliders involved.
		* 
		* \param info Collision information containing data about both colliders.
		*/
	void determine_collision_handler(CollisionInfo& info);

	/**
		* \brief Handles collisions involving static objects.
		* 
		* Resolves collisions by adjusting positions and modifying velocities if bounce is enabled.
		* 
		* \param info Collision information containing data about both colliders.
		*/
	void static_collision_handler(CollisionInfo& info);
private:
	
	/**
		* \brief Checks for collisions between colliders.
		* 
		* Identifies collisions and generates pairs of colliding objects for further processing.
		* 
		* \param colliders A collection of all active colliders.
		* \return A list of collision pairs with their associated data.
		*/
	std::vector<std::pair<CollisionInternal,CollisionInternal>> check_collisions(std::vector<collider_variant> & colliders);

	/**
		* \brief Checks for collision between two colliders.
		* 
		* Calls the appropriate collision detection function based on the collider types.
		* 
		* \param collider1 The first collider.
		* \param components1 Transform and Rigidbody of the first object.
		* \param collider2 The second collider.
		* \param components2 Transform and Rigidbody of the second object.
		* \param type The type of collider pair.
		* \return True if a collision is detected, otherwise false.
		*/
	bool check_collision(const collider_variant& collider1,std::pair<std::reference_wrapper<Transform>, std::reference_wrapper<Rigidbody>> components1,const collider_variant& collider2,std::pair<std::reference_wrapper<Transform>, std::reference_wrapper<Rigidbody>> components2,CollisionSystem::CollisionInternalType type);
	
	/**
		* \brief Retrieves the active Transform and Rigidbody components for a given game object.
		* 
		* This function looks up the Transform and Rigidbody components associated with the specified 
		* game object ID. It checks if both components are present and active. If both are found 
		* to be active, they are returned wrapped in reference wrappers; otherwise, an empty 
		* optional is returned.
		*
		* \param game_object_id The ID of the game object for which to retrieve the components.
		* 
		* \return A std::optional containing a pair of reference wrappers to the active Transform 
		*         and Rigidbody components, or std::nullopt if either component is not found 
		*         or not active.
		*/
	std::optional<std::pair<std::reference_wrapper<Transform>, std::reference_wrapper<Rigidbody>>> get_active_transform_and_rigidbody(game_object_id_t game_object_id);


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
	bool check_box_box_collision(const BoxCollider& box1, const BoxCollider& box2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2);
	
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
	bool check_box_circle_collision(const BoxCollider& box1, const CircleCollider& circle2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2);

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
	bool check_circle_circle_collision(const CircleCollider& circle1, const CircleCollider& circle2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2);
};

} // namespace crepe
