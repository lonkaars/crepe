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
	// using collider_stor = std::variant<BoxCollider, CircleCollider>;
	using collider_variant = std::variant<std::reference_wrapper<BoxCollider>, std::reference_wrapper<CircleCollider>>;

	//! A enum that is used to tell the pair of the collider stor in a std::pair.
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
    NONE,
    X_DIRECTION,
    Y_DIRECTION,
    BOTH
	};

public:
	/**
		* \brief A structure representing detailed collision information between two colliders.
		* 
		* This includes the movement data required to resolve the collision.
		*/
	struct CollisionInfo{
    Collider& first_collider;
		Transform& first_transform;
		Rigidbody& first_rigidbody;
    Collider& second_collider;
		Transform& second_transform;
		Rigidbody& second_rigidbody;
		vec2 resolution;
		Direction resolution_direction = Direction::NONE;
	};

public:

	//! Updates the collision system by checking for collisions between colliders and handling them.
	void update() override;
private: //generic

	/**
	 * \brief Returns a type of the colliders combined into a pair.
	 * 
	 * This function uses the holds_alternative to determine what both colliders are.
	 * This caluclated value is returned so get can be savely used.
	 *
	 * \param collider1 Variant of collider. Can be a box or circle collider
	 * \param collider2 Variant of collider. Can be a box or circle collider
	 *
	 * \return collider pair type.
	 */
	CollisionInternalType check_collider_type(const collider_variant& collider1,const collider_variant& collider2);

	/**
	 * \brief Calculates the position of the Collider
	 * 
	 * Using the \c Collider offset, \c Transform position and \c Rigidbody offset the place of the collider is calculated.
	 *
	 * \param collider_offset Collider offset value.
	 * \param transform Transform of same gameobject as collider.
	 * \param rigidbody Rigidbody of same gameobject as collider. 
	 *
	 * \return Postion of collider.
	 */
	vec2 current_position(vec2 collider_offset, const Transform& transform, const Rigidbody& rigidbody);

private:// handeling

	/**
	 * \brief Calculates the position of the Collider
	 * 
	 * Using the \c Collider offset, \c Transform position and \c Rigidbody offset the place of the collider is calculated.
	 *
	 * \param collider_offset Collider offset value.
	 * \param transform Transform of same gameobject as collider.
	 * \param rigidbody Rigidbody of same gameobject as collider. 
	 *
	 * \return Postion of collider.
	 */
	void collision_handler_request(CollisionInternal& data1,CollisionInternal& data2);

	/**
	 * \brief Calculates the move back value and direction of the Collision
	 * 
	 * Uses data from both gameobjects to calculate the value of the gameobject to move out of other collider. 
	 *
	 * \param data1 Has data about the first gameobject of the collision
	 * \param data2 Has data about the second gameobject of the collision
	 * \param type Type of collider pair used for variant
	 *
	 * \return Move back value and direction for first gameobject
	 */
	std::pair<vec2,Direction> collision_handler(CollisionInternal& data1,CollisionInternal& data2 ,CollisionInternalType type);

	/**
	 * \brief Calculates the move back value for box box collision
	 * 
	 * Uses both collider and positions to calculate move back value 
	 *
	 * \param box_collider1 First boxcollider of collision
	 * \param box_collider2 Second boxcollider of collision
	 * \param position1 Position of first boxcollider
	 * \param position2 Position of second boxcollider
	 *
	 * \return Move back value and direction for first gameobject
	 */
	vec2 box_box_move_back(const BoxCollider& box_collider1,const BoxCollider& box_collider2,vec2 position1,vec2 position2);

	/**
	 * \brief Determines what collision handler is called
	 * 
	 * If the object is static is does nothing.
	 * If the object is dynamic and collides with not static object it calls the script collision handeler.
	 * If the object is dynamic and collides with static it handles it and calls the script collision handeler.
	 *
	 * \param info Collision info of both gameobjects
	 */
	void determine_collision_handler(CollisionInfo& info);

	/**
	 * \brief handles static collision
	 * 
	 * Moves the object back out of static gameobject.
	 * If bounce is active change velocity.
	 *
	 * \param info Collision info of both gameobjects
	 */
	void static_collision_handler(CollisionInfo& info);
private: // detection
	
	/**
	 * \brief Checks if there is an collision between two colliders
	 * 
	 * Does not use the type of a collider to determine if there is collision.
	 * uses variant with comment data to determine if even collision needs to be checked.
	 *
	 * \param colliders Holds all colliders
	 *
	 * \return Move back value and direction for first gameobject
	 */
	std::vector<std::pair<CollisionInternal,CollisionInternal>> check_collisions(std::vector<collider_variant> & colliders);

	/**
	 * \brief Calls the correct check collision function.
	 * 
	 * Uses the type to check what colliders are used, converts the colliders and calls the check function.
	 *
	 * \param collider1 First collider
	 * \param components1 Transform and rigidbody from first object
	 * \param collider2 Second collider
	 * \param components2 Transform and rigidbody from second object
	 * \param type Type of collider pair
	 *
	 * \return status of collision
	 */
	bool check_collision(const collider_variant& collider1,std::pair<std::reference_wrapper<Transform>, std::reference_wrapper<Rigidbody>> components1,const collider_variant& collider2,std::pair<std::reference_wrapper<Transform>, std::reference_wrapper<Rigidbody>> components2,CollisionSystem::CollisionInternalType type);
	
	/**
	 * \brief Check collision for box on box collider
	 *
	 * \param box1 First collider
	 * \param box2 Second collider
	 * \param transform1 Transform of first object
	 * \param transform2 Transform of second object
	 * \param rigidbody1 Rigidbody of first object
	 * \param rigidbody2 Rigidbody of second object
	 *
	 * \return status of collision
	 */
	bool check_box_box_collision(const BoxCollider& box1, const BoxCollider& box2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2);
	
	/**
	 * \brief Check collision for box on circle collider
	 *
	 * \param box1 First collider
	 * \param circle2 Second collider
	 * \param transform1 Transform of first object
	 * \param transform2 Transform of second object
	 * \param rigidbody1 Rigidbody of first object
	 * \param rigidbody2 Rigidbody of second object
	 *
	 * \return status of collision
	 */
	bool check_box_circle_collision(const BoxCollider& box1, const CircleCollider& circle2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2);

	/**
	 * \brief Check collision for circle on circle collider
	 *
	 * \param circle1 First collider
	 * \param circle2 Second collider
	 * \param transform1 Transform of first object
	 * \param transform2 Transform of second object
	 * \param rigidbody1 Rigidbody of first object
	 * \param rigidbody2 Rigidbody of second object
	 *
	 * \return status of collision
	 */
	bool check_circle_circle_collision(const CircleCollider& circle1, const CircleCollider& circle2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2);
};

} // namespace crepe
