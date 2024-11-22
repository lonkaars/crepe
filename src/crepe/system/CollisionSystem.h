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
	using collider_stor = std::variant<std::reference_wrapper<BoxCollider>, std::reference_wrapper<CircleCollider>>;

	//! A enum that is used to tell the pair of the collider stor in a std::pair.
	enum class ColliderStorType {
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
	struct CollidedInfoStor {
		//! Store either BoxCollider or CircleCollider
		collider_stor& collider; 
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
		vec2 move_back_value;
		Direction move_back_direction = Direction::NONE;
	};

public:

	//! Updates the collision system by checking for collisions between colliders and handling them.
	void update() override;
private: //generic
	ColliderStorType check_collider_type(const collider_stor& collider1,const collider_stor& collider2);

	vec2 current_position(vec2 collider_offset, const Transform& transform, const Rigidbody& rigidbody);

private:// handeling

	void collision_handler_request(CollidedInfoStor& data1,CollidedInfoStor& data2);

	std::pair<vec2,Direction> collision_handler(CollidedInfoStor& data1,CollidedInfoStor& data2 ,ColliderStorType type);


	
	vec2 box_box_move_back(const BoxCollider& box_collider1,const BoxCollider& box_collider2,vec2 position1,vec2 position2);

	void determine_collision_handler(CollisionInfo& info);

	void static_collision_handler(CollisionInfo& info);
private: // detection
	
	std::vector<std::pair<CollidedInfoStor,CollidedInfoStor>> check_collisions(std::vector<collider_stor> & colliders);

	bool check_collision(const collider_stor& collider1,std::pair<std::reference_wrapper<Transform>, std::reference_wrapper<Rigidbody>> components1,const collider_stor& collider2,std::pair<std::reference_wrapper<Transform>, std::reference_wrapper<Rigidbody>> components2,CollisionSystem::ColliderStorType type);
	
	bool check_box_box_collision(const BoxCollider& box1, const BoxCollider& box2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2);
	
	bool check_box_circle_collision(const BoxCollider& box1, const CircleCollider& circle2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2);

	bool check_circle_circle_collision(const CircleCollider& circle1, const CircleCollider& circle2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2);
};

} // namespace crepe
