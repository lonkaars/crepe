#include <cmath>

#include "CollisionSystem.h"

#include "../ComponentManager.h"
#include "../api/BoxCollider.h"
#include "../api/CircleCollider.h"
#include "../api/Vector2.h"
#include "../api/Rigidbody.h"
#include "../api/Transform.h"

#include "Collider.h"
#include "iostream"

using namespace crepe;

CollisionSystem::CollisionSystem() {}

void CollisionSystem::update() {
	ComponentManager & mgr = ComponentManager::get_instance();
	std::vector<std::reference_wrapper<BoxCollider>> boxcolliders	= mgr.get_components_by_type<BoxCollider>();
	
	Transform & transform1 = mgr.get_components_by_id<Transform>(boxcolliders[0].get().game_object_id).front().get();
	Rigidbody & rigidbody1 = mgr.get_components_by_id<Rigidbody>(boxcolliders[0].get().game_object_id).front().get();
	Transform & transform2 = mgr.get_components_by_id<Transform>(boxcolliders[1].get().game_object_id).front().get();
	Rigidbody & rigidbody2 = mgr.get_components_by_id<Rigidbody>(boxcolliders[1].get().game_object_id).front().get();
	BoxCollider & collider1 = boxcolliders[0].get();
	BoxCollider & collider2 = boxcolliders[1].get();
	bool test = check_box_box_collision(collider1, collider2, transform1, transform2, rigidbody1, rigidbody2);
	std::cout << "collided? " << test << std::endl;
}



bool CollisionSystem::check_collisions(const std::vector<Collider*>& colliders1, const std::vector<Collider*>& colliders2) {}
bool CollisionSystem::check_box_box_collision(const BoxCollider& box1, const BoxCollider& box2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2)
{
	// Function to convert degrees to radians
	auto degrees_to_radians = [](double degrees) {
			return degrees * (M_PI / 180.0);
	};

	// Get the rotation in radians
	double radians1 = degrees_to_radians(transform1.rotation);
	double radians2 = degrees_to_radians(transform2.rotation);

	// Calculate the scale factor (for both rigidbody and box offsets)
	double scale1 = transform1.scale;
	double scale2 = transform2.scale;

	Vector2 total_offset1 = (rigidbody1.data.offset + box1.offset) * transform1.scale;
	Vector2 total_offset2 = (rigidbody2.data.offset + box2.offset) * transform2.scale;

	// Rotate
	double rotated_total_offset_x1 = total_offset1.x * cos(radians1) - total_offset1.y * sin(radians1);
	double rotated_total_offset_y1 = total_offset1.x * sin(radians1) + total_offset1.y * cos(radians1);

	double rotated_total_offset_x2 = total_offset2.x * cos(radians2) - total_offset2.y * sin(radians2);
	double rotated_total_offset_y2 = total_offset2.x * sin(radians2) + total_offset2.y * cos(radians2);

	// Final positions considering scaling and rotation
	Vector2 final_position1 = transform1.position + Vector2(rotated_total_offset_x1, rotated_total_offset_y1);
	Vector2 final_position2 = transform2.position + Vector2(rotated_total_offset_x2, rotated_total_offset_y2);

	 // Log final positions for debugging purposes
	std::cout << "Final Position of Box 1: (" << final_position1.x << ", " << final_position1.y << ")" << std::endl;
	std::cout << "Final Position of Box 2: (" << final_position2.x << ", " << final_position2.y << ")" << std::endl;

	// Log rotation values for debugging
	std::cout << "Rotation of Box 1: " << transform1.rotation << " degrees" << std::endl;
	std::cout << "Rotation of Box 2: " << transform2.rotation << " degrees" << std::endl;


	// Calculate half-extents (half width and half height)
	double half_width1 = box1.width / 2.0;
	double half_height1 = box1.height / 2.0;
	double half_width2 = box2.width / 2.0;
	double half_height2 = box2.height / 2.0;

	// Check if the boxes overlap along the X and Y axes
	return !(final_position1.x + half_width1 < final_position2.x - half_width2 ||  // box1 is left of box2
						final_position1.x - half_width1 > final_position2.x + half_width2 ||  // box1 is right of box2
						final_position1.y + half_height1 < final_position2.y - half_height2 || // box1 is above box2
						final_position1.y - half_height1 > final_position2.y + half_height2);  // box1 is below box2
}
bool CollisionSystem::check_box_circle_collision(const BoxCollider& box, const CircleCollider& circle) {}
bool CollisionSystem::check_circle_circle_collision(const CircleCollider& circle1, const CircleCollider& circle2) {}
