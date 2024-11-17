#pragma once

#include "Collider.h"
#include "api/Rigidbody.h"
#include "api/Transform.h"
#include "api/BoxCollider.h"
#include "api/CircleCollider.h"
#include "api/Vector2.h"
#include <tuple>
#include <vector>
#include <variant>

namespace crepe {


class CollisionSystem {
private:
	using collider_stor = std::variant<BoxCollider, CircleCollider>;
private:
	struct CollidedInfoStor {
		//! Store either BoxCollider or CircleCollider
		collider_stor collider; 
		Transform& transform;
		Rigidbody& rigidbody;      // Rigidbody data
	};
public:
	struct ColliderInfo {
		const Collider& collider;
		Transform& transform;
		Rigidbody& rigidbody;
	};
	struct CollisionInfo{
    ColliderInfo first;
    ColliderInfo second;
		Vector2 move_back_value;
	};
public:
	CollisionSystem();
	void update();
private: //handling
	void call_collision_handler(CollidedInfoStor& data1,CollidedInfoStor& data2);
	void static_collision_handler(CollisionInfo& info);
private: //detection
	
	std::vector<std::pair<CollidedInfoStor,CollidedInfoStor>> check_collisions(const std::vector<std::reference_wrapper<BoxCollider>>& boxcolliders, const std::vector<std::reference_wrapper<CircleCollider>>& circlecolliders);
	bool check_box_box_collision(const BoxCollider& box1, const BoxCollider& box2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2);
	bool check_box_circle_collision(const BoxCollider& box1, const CircleCollider& circle2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2);
	bool check_circle_circle_collision(const CircleCollider& circle1, const CircleCollider& circle2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2);
	Vector2 current_position(const Collider& collider, const Transform& transform, const Rigidbody& rigidbody);


};

} // namespace crepe
