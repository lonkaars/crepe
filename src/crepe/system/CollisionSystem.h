#pragma once

#include "Collider.h"
#include <vector>
#include <variant>

namespace crepe {

class Collider;
class BoxCollider;
class CircleCollider;
class Transform;
class Rigidbody;

class CollisionSystem {
public:
	CollisionSystem();
	void update();
private:
	using collider_stor = std::variant<BoxCollider, CircleCollider>;
private:
	void call_collision_handler(const Rigidbody& rigidbody1,const Rigidbody& rigidbody2);
  std::vector<std::pair<collider_stor, collider_stor>> check_collisions(const std::vector<std::reference_wrapper<BoxCollider>>& boxcolliders, const std::vector<std::reference_wrapper<CircleCollider>>& circlecolliders);
	bool check_box_box_collision(const BoxCollider& box1, const BoxCollider& box2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2);
	bool check_box_circle_collision(const BoxCollider& box1, const CircleCollider& circle2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2);
	bool check_circle_circle_collision(const CircleCollider& circle1, const CircleCollider& circle2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2);
	Vector2 current_position(const Collider& collider, const Transform& transform, const Rigidbody& rigidbody);
};

} // namespace crepe
