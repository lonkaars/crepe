#pragma once

#include "Collider.h"
#include "api/Rigidbody.h"
#include "api/Transform.h"
#include "api/BoxCollider.h"
#include "api/CircleCollider.h"
#include <tuple>
#include <vector>
#include <variant>

namespace crepe {


class CollisionSystem {
private:
	using collider_stor = std::variant<BoxCollider, CircleCollider>;
private:
	struct CollidedInfoStor {
		collider_stor collider;  // Store either BoxCollider or CircleCollider
		Transform transform;      // Transform data
		Rigidbody rigidbody;      // Rigidbody data
	};
public:
	CollisionSystem();
	void update();
private:
	void call_collision_handler(const CollidedInfoStor& data1,const CollidedInfoStor& data2);
  std::vector<std::pair<CollidedInfoStor,CollidedInfoStor>> check_collisions(const std::vector<std::reference_wrapper<BoxCollider>>& boxcolliders, const std::vector<std::reference_wrapper<CircleCollider>>& circlecolliders);
	bool check_box_box_collision(const BoxCollider& box1, const BoxCollider& box2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2);
	bool check_box_circle_collision(const BoxCollider& box1, const CircleCollider& circle2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2);
	bool check_circle_circle_collision(const CircleCollider& circle1, const CircleCollider& circle2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2);
	Vector2 current_position(const Collider& collider, const Transform& transform, const Rigidbody& rigidbody);
};

} // namespace crepe
