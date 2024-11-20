#pragma once

#include <vector>
#include <variant>

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
	using collider_stor = std::variant<BoxCollider, CircleCollider>;

	/**
		* \brief A structure to store the collision data of a single collider.
		* 
		* This structure stores the collider type, its associated transform, and its rigidbody.
		*/
	struct CollidedInfoStor {
		//! Store either BoxCollider or CircleCollider
		collider_stor collider; 
		Transform& transform;
		Rigidbody& rigidbody;
	};
	
	//! Enum representing movement directions during collision resolution.
	enum class Direction {
    NONE,
    X_DIRECTION,
    Y_DIRECTION,
    BOTH
	};

public:
	/**
		* \brief A structure representing the collision information between two colliders.
		* 
		* This structure contains both colliders, their associated transforms and rigidbodies,
		* as well as the movement vector to resolve the collision.
		*/
	struct ColliderInfo {
		const Collider& collider;
		Transform& transform;
		Rigidbody& rigidbody;
	};
	/**
		* \brief A structure representing detailed collision information between two colliders.
		* 
		* This includes the movement data required to resolve the collision.
		*/
	struct CollisionInfo{
    ColliderInfo first;
    ColliderInfo second;
		Vector2 move_back_value;
		Direction move_back_direction = Direction::NONE;
	};

public:

	//! Updates the collision system by checking for collisions between colliders and handling them.
	void update() override;

private:
	/**
		* \brief Handles a collision between two colliders.
		* 
		* This function calculates the necessary response to resolve the collision, including
		* moving the objects back to prevent overlap and applying any velocity changes.
		*
		* \param data1 The collision data for the first collider.
		* \param data2 The collision data for the second collider.
		*/
	void collision_handler(CollidedInfoStor& data1,CollidedInfoStor& data2);
	
	/**
		* \brief Resolves the movement of two box colliders that are colliding.
		* 
		* This function calculates the smallest overlap (along the X or Y axis) and determines
		* the move-back vector to prevent overlap.
		*
		* \param box_collider1 The first box collider.
		* \param box_collider2 The second box collider.
		* \param final_position1 The final position of the first box collider.
		* \param final_position2 The final position of the second box collider.
		* \return The move-back vector to resolve the collision.
		*/
	Vector2 box_box_collision_move_back(const BoxCollider& box_collider1,const BoxCollider& box_collider2,Vector2 position1,Vector2 position2);

	/**
		* \brief Determines the appropriate collision handler based on the rigidbody types of the colliding objects.
		* 
		* This function checks if the second object is static, and if so, it calls the static collision handler.
		* Otherwise, it triggers a collision event.
		*
		* \param info The collision information containing the colliders, transforms, rigidbodies, and move-back data.
		*/
	void determine_collision_handler(CollisionInfo& info);

	/**
		* \brief Handles the collision with a static object.
		* 
		* This function resolves the collision by moving the object back and applying any bounce or stop behavior.
		*
		* \param info The collision information containing the colliders, transforms, rigidbodies, and move-back data.
		*/
	void static_collision_handler(CollisionInfo& info);
private: //detection
	
	/**
		* \brief Checks for collisions between box colliders and circle colliders
		* and returns the collision pairs that need to be resolved.
		* 
		* \param boxcolliders A vector of references to all box colliders.
		* \param circlecolliders A vector of references to all circle colliders.
		* \return A vector of pairs containing collision information for the detected collisions.
		*/
	std::vector<std::pair<CollidedInfoStor,CollidedInfoStor>> check_collisions(const std::vector<std::reference_wrapper<BoxCollider>>& boxcolliders, const std::vector<std::reference_wrapper<CircleCollider>>& circlecolliders);
	
	/**
		* \brief Checks for a collision between two box colliders.
		* 
		* This function checks if two box colliders overlap based on their positions and dimensions.
		*
		* \param box1 The first box collider.
		* \param box2 The second box collider.
		* \param transform1 The transform component of the first box collider.
		* \param transform2 The transform component of the second box collider.
		* \param rigidbody1 The rigidbody component of the first box collider.
		* \param rigidbody2 The rigidbody component of the second box collider.
		* \return True if the two box colliders overlap, otherwise false.
		*/
	bool check_box_box_collision(const BoxCollider& box1, const BoxCollider& box2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2);
	
	/**
		* \brief Checks for a collision between a box collider and a circle collider.
		* 
		* This function checks if a box collider overlaps with a circle collider based on their positions
		* and dimensions.
		*
		* \param box1 The box collider.
		* \param circle2 The circle collider.
		* \param transform1 The transform component of the box collider.
		* \param transform2 The transform component of the circle collider.
		* \param rigidbody1 The rigidbody component of the box collider.
		* \param rigidbody2 The rigidbody component of the circle collider.
		* \return True if the box collider and circle collider overlap, otherwise false.
		*/
	bool check_box_circle_collision(const BoxCollider& box1, const CircleCollider& circle2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2);
	
	/**
		* \brief Checks for a collision between two circle colliders.
		* 
		* This function checks if two circle colliders overlap based on their positions and radii.
		*
		* \param circle1 The first circle collider.
		* \param circle2 The second circle collider.
		* \param transform1 The transform component of the first circle collider.
		* \param transform2 The transform component of the second circle collider.
		* \param rigidbody1 The rigidbody component of the first circle collider.
		* \param rigidbody2 The rigidbody component of the second circle collider.
		* \return True if the two circle colliders overlap, otherwise false.
		*/
	bool check_circle_circle_collision(const CircleCollider& circle1, const CircleCollider& circle2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2);
	
	/**
		* \brief Gets the current position of a collider by combining its transform and rigidbody data.
		* 
		* This function calculates the current position of the collider by considering its transform and 
		* rigidbody velocity.
		*
		* \param collider The collider whose position is being determined.
		* \param transform The transform component associated with the collider.
		* \param rigidbody The rigidbody component associated with the collider.
		* \return The current position of the collider as a Vector2.
		*/
	Vector2 current_position(const Collider& collider, const Transform& transform, const Rigidbody& rigidbody);
};

} // namespace crepe
