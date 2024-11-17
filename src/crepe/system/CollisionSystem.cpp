#include <cmath>
#include <algorithm>
#include <cstddef>
#include <utility>
#include <variant>

#include "CollisionSystem.h"
#include "../api/Event.h"
#include "../api/EventManager.h"

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
	std::vector<std::reference_wrapper<CircleCollider>> circlecolliders	= mgr.get_components_by_type<CircleCollider>();
	std::vector<std::pair<CollidedInfoStor,CollidedInfoStor>> collided = check_collisions(boxcolliders,circlecolliders);
	// std::cout << "DEBUG INFO" << std::endl;
	for (const auto& collision_pair : collided) {
		call_collision_handler(collision_pair.first,collision_pair.second); // First collider
		call_collision_handler(collision_pair.second,collision_pair.first); // First collider
	}

	if(collided.empty()) {
		std::cout << "No objects collided" << std::endl;
	}
}

void CollisionSystem::call_collision_handler(const CollidedInfoStor& data1,const CollidedInfoStor& data2){
	const Collider* collider1 = nullptr;
	const Collider* collider2 = nullptr;
	// Check collision type and get values for handler
	game_object_id_t first = 0,second = 0;
	if (std::holds_alternative<BoxCollider>(data1.collider)) {
		if (std::holds_alternative<BoxCollider>(data2.collider)) {
			const BoxCollider& box_collider1 = std::get<BoxCollider>(data1.collider);
			const BoxCollider& box_collider2 = std::get<BoxCollider>(data2.collider);
			collider1 = &box_collider1;
			collider2 = &box_collider2;
			first = box_collider1.game_object_id;
			second = box_collider2.game_object_id;
		}
		else {
			const BoxCollider& box_collider = std::get<BoxCollider>(data1.collider);
			const CircleCollider& circle_collider = std::get<CircleCollider>(data2.collider);
			collider1 = &box_collider;
			collider2 = &circle_collider;
			first = box_collider.game_object_id;
			second = circle_collider.game_object_id;
		}
	}
	else {
		if (std::holds_alternative<CircleCollider>(data2.collider)) {
			const CircleCollider& circle_collider1 = std::get<CircleCollider>(data1.collider);
			const CircleCollider& circle_collider2 = std::get<CircleCollider>(data2.collider);
			collider1 = &circle_collider1;
			collider2 = &circle_collider2;
			first = circle_collider1.game_object_id;
			second = circle_collider2.game_object_id;
		}
		else {
			const CircleCollider& circle_collider = std::get<CircleCollider>(data1.collider);
			const BoxCollider& box_collider = std::get<BoxCollider>(data2.collider);
			collider1 = &circle_collider;
			collider2 = &box_collider;
			first = circle_collider.game_object_id;
			second = box_collider.game_object_id;
		}
	}

	// check rigidbody type
	if(data1.rigidbody.data.body_type != Rigidbody::BodyType::STATIC)
	{
		// If second body is static move back
		if(data2.rigidbody.data.body_type == Rigidbody::BodyType::STATIC){
			//call static handler (is bounce true?)
		}; 
		
		crepe::CollisionSystem::CollisionInfo collision_info{
            { *collider1, data1.transform, data1.rigidbody },
            { *collider2, data2.transform, data2.rigidbody }
        };
		CollisionEvent data(collision_info);
		EventManager::get_instance().trigger_event<CollisionEvent>(data, first);
	}		
}

std::vector<std::pair<CollisionSystem::CollidedInfoStor,CollisionSystem::CollidedInfoStor>> CollisionSystem::check_collisions(const std::vector<std::reference_wrapper<BoxCollider>>& boxcolliders, const std::vector<std::reference_wrapper<CircleCollider>>& circlecolliders) {
	ComponentManager & mgr = ComponentManager::get_instance();
	std::vector<std::pair<CollidedInfoStor,CollidedInfoStor>> collisions_ret;
	//if no colliders skip
	//check if colliders has rigibocdy if not skip

	//if amount is higer than lets say 16 for now use quadtree otwerwise skip
	//quadtree code
	//quadtree is placed over the input vector

	// Check collisions
	for (size_t i = 0; i < boxcolliders.size(); ++i) {
		// Fetch components for the first box collider
		if(!boxcolliders[i].get().active) continue;
		int game_object_id_1 = boxcolliders[i].get().game_object_id;
		Transform& transform1 = mgr.get_components_by_id<Transform>(game_object_id_1).front().get();
		if(!transform1.active) continue;
		Rigidbody& rigidbody1 = mgr.get_components_by_id<Rigidbody>(game_object_id_1).front().get();
		if(!rigidbody1.active) continue;
		
		// Check CircleCollider vs CircleCollider
		for (size_t j = i + 1; j < boxcolliders.size(); ++j) {
			if(!boxcolliders[j].get().active) continue;
			// Skip self collision
			int game_object_id_2 = boxcolliders[j].get().game_object_id;
			if (game_object_id_1 == game_object_id_2) continue;

			// Fetch components for the second box collider
			Transform & transform2 = mgr.get_components_by_id<Transform>(boxcolliders[j].get().game_object_id).front().get();
			if(!transform2.active) continue;
			Rigidbody & rigidbody2 = mgr.get_components_by_id<Rigidbody>(boxcolliders[j].get().game_object_id).front().get();
			if(!rigidbody2.active) continue;
			// Check collision
			if (check_box_box_collision(boxcolliders[i], boxcolliders[j], transform1, transform2, rigidbody1, rigidbody2)) {
				collisions_ret.emplace_back(std::make_pair(
				CollidedInfoStor{boxcolliders[i], transform1, rigidbody1}, 
				CollidedInfoStor{boxcolliders[j], transform2, rigidbody2}
				));
			}
		}

		// Check BoxCollider vs CircleCollider
		for (size_t j = 0; j < circlecolliders.size(); ++j) {
			if(!circlecolliders[j].get().active) continue;
			// Skip self collision
			int game_object_id_2 = circlecolliders[j].get().game_object_id;
			if (game_object_id_1 == game_object_id_2) continue;

			// Fetch components for the second collider (circle)
			Transform & transform2 = mgr.get_components_by_id<Transform>(circlecolliders[j].get().game_object_id).front().get();
			if(!transform2.active) continue;
			Rigidbody & rigidbody2 = mgr.get_components_by_id<Rigidbody>(circlecolliders[j].get().game_object_id).front().get();
			if(!rigidbody2.active) continue;

			// Check collision
			if (check_box_circle_collision(boxcolliders[i], circlecolliders[j], transform1, transform2, rigidbody1, rigidbody2)) {
				
				collisions_ret.emplace_back(std::make_pair(
				CollidedInfoStor{boxcolliders[i], transform1, rigidbody1}, 
				CollidedInfoStor{circlecolliders[j], transform2, rigidbody2}
				));
			}
		}
	}
	// Check CircleCollider vs CircleCollider
	for (size_t i = 0; i < circlecolliders.size(); ++i) {
		if(!circlecolliders[i].get().active) continue;
		// Fetch components for the first circle collider
		int game_object_id_1 = circlecolliders[i].get().game_object_id;
		Transform & transform1 = mgr.get_components_by_id<Transform>(circlecolliders[i].get().game_object_id).front().get();
		if(!transform1.active) continue;
		Rigidbody & rigidbody1 = mgr.get_components_by_id<Rigidbody>(circlecolliders[i].get().game_object_id).front().get();
		if(!rigidbody1.active) continue;

		for (size_t j = i + 1; j < circlecolliders.size(); ++j) {
			if(!circlecolliders[j].get().active) continue;
			// Skip self collision
			int game_object_id_2 = circlecolliders[j].get().game_object_id;
			if (game_object_id_1 == game_object_id_2) continue;

			// Fetch components for the second circle collider
			Transform & transform2 = mgr.get_components_by_id<Transform>(circlecolliders[j].get().game_object_id).front().get();
			if(!transform2.active) continue;
			Rigidbody & rigidbody2 = mgr.get_components_by_id<Rigidbody>(circlecolliders[j].get().game_object_id).front().get();
			if(!rigidbody2.active) continue;

			// Check collision
			if (check_circle_circle_collision(circlecolliders[i], circlecolliders[j], transform1, transform2, rigidbody1, rigidbody2)) {
				collisions_ret.emplace_back(std::make_pair(
				CollidedInfoStor{circlecolliders[i], transform1, rigidbody1}, 
				CollidedInfoStor{circlecolliders[j], transform2, rigidbody2}
				));
			}
		}
	}
	return collisions_ret;
}

bool CollisionSystem::check_box_box_collision(const BoxCollider& box1, const BoxCollider& box2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2)
{
	// Get current positions of colliders
	Vector2 final_position1 = current_position(box1,transform1,rigidbody1);
	Vector2 final_position2 = current_position(box2,transform2,rigidbody2);

	 // Log final positions for debugging purposes
	// std::cout << "Final Position of Box 1: (" << final_position1.x << ", " << final_position1.y << ")" << std::endl;
	// std::cout << "Final Position of Box 2: (" << final_position2.x << ", " << final_position2.y << ")" << std::endl;

	// Log rotation values for debugging
	// std::cout << "Rotation of Box 1: " << transform1.rotation << " degrees" << std::endl;
	// std::cout << "Rotation of Box 2: " << transform2.rotation << " degrees" << std::endl;


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

bool CollisionSystem::check_box_circle_collision(const BoxCollider& box1, const CircleCollider& circle2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2) {
	// Get current positions of colliders
	Vector2 final_position1 = current_position(box1, transform1, rigidbody1);
	Vector2 final_position2 = current_position(circle2, transform2, rigidbody2);

	// Log final positions for debugging purposes
	// std::cout << "Final Position of Box: (" << final_position1.x << ", " << final_position1.y << ")" << std::endl;
	// std::cout << "Final Position of Circle: (" << final_position2.x << ", " << final_position2.y << ")" << std::endl;

	// Calculate box half-extents
	double half_width = box1.width / 2.0;
	double half_height = box1.height / 2.0;

	// Find the closest point on the box to the circle's center
	double closest_x = std::max(final_position1.x - half_width, std::min(final_position2.x, final_position1.x + half_width));
	double closest_y = std::max(final_position1.y - half_height, std::min(final_position2.y, final_position1.y + half_height));


	// Calculate the distance squared between the circle's center and the closest point on the box
	double distance_x = final_position2.x - closest_x;
	double distance_y = final_position2.y - closest_y;
	double distance_squared = distance_x * distance_x + distance_y * distance_y;

	// Compare distance squared with the square of the circle's radius
	return distance_squared <= circle2.radius * circle2.radius;
}

bool CollisionSystem::check_circle_circle_collision(const CircleCollider& circle1, const CircleCollider& circle2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2) {
	// Get current positions of colliders
	Vector2 final_position1 = current_position(circle1,transform1,rigidbody1);
	Vector2 final_position2 = current_position(circle2,transform2,rigidbody2);

	// Log final positions for debugging purposes
	// std::cout << "Final Position of Circle 1: (" << final_position1.x << ", " << final_position1.y << ")" << std::endl;
	// std::cout << "Final Position of Circle 2: (" << final_position2.x << ", " << final_position2.y << ")" << std::endl;

	// Log rotation values for debugging (circles do not rotate, so this might not be needed for circles)
	// std::cout << "Rotation of Circle 1: " << transform1.rotation << " degrees" << std::endl;
	// std::cout << "Rotation of Circle 2: " << transform2.rotation << " degrees" << std::endl;

	double distance_x = final_position1.x - final_position2.x;
	double distance_y = final_position1.y - final_position2.y;
	double distance_squared = distance_x * distance_x + distance_y * distance_y;

	// Calculate the sum of the radii
	double radius_sum = circle1.radius + circle2.radius;

	// Check if the distance between the centers is less than or equal to the sum of the radii
	return distance_squared <= radius_sum * radius_sum;
}

Vector2 CollisionSystem::current_position(const Collider& collider, const Transform& transform, const Rigidbody& rigidbody) {
	// Function to convert degrees to radians
	auto degrees_to_radians = [](double degrees) {
			return degrees * (M_PI / 180.0);
	};

	// Get the rotation in radians
	double radians1 = degrees_to_radians(transform.rotation);

	// Calculate total offset with scale
	Vector2 total_offset = (rigidbody.data.offset + collider.offset) * transform.scale;

	// Rotate
	double rotated_total_offset_x1 = total_offset.x * cos(radians1) - total_offset.y * sin(radians1);
	double rotated_total_offset_y1 = total_offset.x * sin(radians1) + total_offset.y * cos(radians1);

	// Final positions considering scaling and rotation
	return(transform.position + Vector2(rotated_total_offset_x1, rotated_total_offset_y1));

}
