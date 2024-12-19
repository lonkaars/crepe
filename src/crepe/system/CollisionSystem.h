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
		BOTH,
	};

public:
	//! Structure representing components of the collider
	struct ColliderInfo {
		Transform & transform;
		Rigidbody & rigidbody;
		Metadata & metadata;
	};

	/**
		* \brief Structure representing detailed collision information between two colliders.
		*
		* Includes information about the colliding objects and the resolution data for handling the collision.
		*/
	struct CollisionInfo {
		ColliderInfo self;
		ColliderInfo other;
		//! The resolution vector for the collision.
		vec2 resolution;
		//! The direction of movement for resolving the collision.
		Direction resolution_direction = Direction::NONE;
		CollisionInfo operator-() const;
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
		* This structure all components and id that are for needed within this system when calculating or handling collisions.
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

	//! Structure of a collider with additional components
	template <typename ColliderType>
	struct ColliderInternal {
		ColliderType & collider;
		Transform & transform;
		Rigidbody & rigidbody;
	};
	//! Predefined BoxColliderInternal. (System is only made for this type)
	using BoxColliderInternal = ColliderInternal<BoxCollider>;
	//! Predefined CircleColliderInternal. (System is only made for this type)
	using CircleColliderInternal = ColliderInternal<CircleCollider>;

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

private:
	/**
		* \brief Converts internal collision data into user-accessible collision information.
		*
		* This function processes collision data from two colliding entities and packages it
 		* into a structured format that is accessible for further use,
 		* such as resolving collisions and triggering user-defined collision scripts.
		*
		* \param data1 Collision data for the first collider.
		* \param data2 Collision data for the second collider.
		*/
	CollisionInfo get_collision_info(const CollisionInternal & data1,
									 const CollisionInternal & data2) const;

	/**
		* \brief Corrects the collision resolution vector and determines its direction.
		*
		* This function adjusts the provided resolution vector based on the 
		* rigidbody's linear velocity to ensure consistent collision correction. If the resolution 
		* vector has only one non-zero component (either x or y), the missing component is computed 
		* based on the rigidbody's velocity. If both components are non-zero, it indicates a corner 
		* collision. The function also identifies the direction of the resolution and returns it.
		*
		* \param resolution resolution vector that needs to be corrected
		* \param rigidbody rigidbody data used to correct resolution
		* \return A Direction indicating the resolution direction
		*/
	Direction resolution_correction(vec2 & resolution, const Rigidbody::Data & rigidbody);

	/**
		* \brief Determines the appropriate collision handler for a given collision event.
		*
		* This function identifies the correct collision resolution process based on the body types 
		* of the colliders involved in the collision. It delegates 
		* collision handling to specific handlers and calls collision event scripts 
		* as needed.
		*
		* \param info Collision information containing data about both colliders.
		*/
	void determine_collision_handler(const CollisionInfo & info);

	/**
		* \brief Calls both collision script
		*
		* Calls both collision script to let user add additonal handling or handle full collision.
		*
		* \param info Collision information containing data about both colliders.
		*/
	void call_collision_events(const CollisionInfo & info);

	/**
		* \brief Handles collisions involving static objects.
		*
		* This function resolves collisions between static and dynamic objects by adjusting 
		* the position of the static object and modifying the velocity of the dynamic object 
		* if elasticity is enabled. The position of the static object is corrected 
		* based on the collision resolution, and the dynamic object's velocity is adjusted 
 		* accordingly to reflect the collision response.
		*
		* The handling includes stopping movement, applying bouncing based on the elasticity 
 		* coefficient, and adjusting the position of the dynamic object if needed.
		*
		* \param info Collision information containing data about both colliders.
		*/
	void static_collision_handler(const CollisionInfo & info);

	/**
		* \brief Handles collisions involving dynamic objects.
		*
		* Resolves collisions between two dynamic objects by adjusting their positions and modifying 
		* their velocities based on the collision resolution. If elasticity is enabled, 
		* the velocity of both objects is reversed and scaled by the respective elasticity coefficient. 
		* The positions of the objects are adjusted based on the collision resolution.
		*
		* \param info Collision information containing data about both colliders.
		*/
	void dynamic_collision_handler(const CollisionInfo & info);

private:
	/**
		* \brief Checks for collisions between colliders.
		*
		* This function checks all active colliders and identifies pairs of colliding objects.
 		* For each identified collision, the appropriate collision data is returned as pairs for further processing.
		*
		* \param colliders A collection of all active colliders.
		* \return A list of collision pairs with their associated data.
		*/
	std::vector<std::pair<CollisionInternal, CollisionInternal>>
	gather_collisions(std::vector<CollisionInternal> & colliders);

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
	 * \return Returns true if there is at least one comparison found.
	 */
	bool should_collide(const CollisionInternal & self,
						const CollisionInternal & other) const; //done

	/**
		* \brief Checks for collision between two colliders.
		*
		* This function determines whether two colliders are colliding based on their types.
		* It calls the appropriate collision detection function based on the collider pair type and stores the collision resolution data.
		* If a collision is detected, it returns true, otherwise false.
		*
		* \param first_info Collision data for the first collider.
		* \param second_info Collision data for the second collider.
		* \param type The type of collider pair.
		* \return True if a collision is detected, otherwise false.
		*/
	bool detect_collision(CollisionInternal & first_info, CollisionInternal & second_info,
						  const CollisionInternalType & type);

	/**
		* \brief Detects collisions between two BoxColliders.
		*
		* This function checks whether two `BoxCollider` are colliding based on their positions and scaled dimensions.
		* If a collision is detected, it calculates the overlap along the X and Y axes and returns the resolution vector.
		* If no collision is detected, it returns a vector with NaN values.

		* \param box1 Information about the first BoxCollider.
		* \param box2 Information about the second BoxCollider.
		* \return If colliding, returns the resolution vector; otherwise, returns {NaN, NaN}.
		*/
	vec2 get_box_box_detection(const BoxColliderInternal & box1,
							   const BoxColliderInternal & box2) const;

	/**
	 * \brief Check collision for box on circle collider
	 *
	 * This function detects if a collision occurs between a rectangular box and a circular collider.
 	 * If a collision is detected, the function calculates the resolution vector to resolve the collision.
   * If no collision is detected, it returns a vector with NaN values
 	 *
	 * \param box1 Information about the BoxCollider.
	 * \param circle2 Information about the circleCollider.
	 * \return If colliding, returns the resolution vector; otherwise, returns {NaN, NaN}.
	 */
	vec2 get_box_circle_detection(const BoxColliderInternal & box1,
								  const CircleColliderInternal & circle2) const;

	/**
	 * \brief Check collision for circle on circle collider
	 *
	 * This function detects if a collision occurs between two circular colliders. 
	 * If a collision is detected, it calculates the resolution vector to resolve the collision. 
   * If no collision is detected, it returns a vector with NaN values.
	 *
	 * \param circle1 Information about the first circleCollider.
	 * \param circle2 Information about the second circleCollider.
	 * \return If colliding, returns the resolution vector; otherwise, returns {NaN, NaN}.
	 */
	vec2 get_circle_circle_detection(const CircleColliderInternal & circle1,
									 const CircleColliderInternal & circle2) const;
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
