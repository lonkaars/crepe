#include <cmath>
#include <algorithm>
#include <cstddef>
#include <utility>
#include <variant>

#include "api/Event.h"
#include "api/EventManager.h"
#include "api/BoxCollider.h"
#include "api/CircleCollider.h"
#include "api/Vector2.h"
#include "api/Rigidbody.h"
#include "api/Transform.h"

#include "ComponentManager.h"
#include "CollisionSystem.h"
#include "Collider.h"

using namespace crepe;

void CollisionSystem::update() {
	// Get collider components and keep them seperate
	ComponentManager & mgr = this->component_manager;
	std::vector<std::reference_wrapper<BoxCollider>> boxcolliders	= mgr.get_components_by_type<BoxCollider>();
	std::vector<std::reference_wrapper<CircleCollider>> circlecolliders	= mgr.get_components_by_type<CircleCollider>();
	
	// Check between all colliders if there is a collision
	std::vector<std::pair<CollidedInfoStor,CollidedInfoStor>> collided = check_collisions(boxcolliders,circlecolliders);

	// For both objects call the collision handler 
	for (auto& collision_pair : collided) {
		collision_handler(collision_pair.first,collision_pair.second);
		collision_handler(collision_pair.second,collision_pair.first);
	}
}

void CollisionSystem::collision_handler(CollidedInfoStor& data1,CollidedInfoStor& data2){

	// Data needed for collision handler info
	const Collider* collider1 = nullptr;
	const Collider* collider2 = nullptr;
	Vector2 move_back;

	// Check collision type and get values for handler
	if (std::holds_alternative<BoxCollider>(data1.collider)) {
		if (std::holds_alternative<BoxCollider>(data2.collider)) {
			
			// Get colliders from variant to be used to determine collision handler info
			const BoxCollider& box_collider1 = std::get<BoxCollider>(data1.collider);
			const BoxCollider& box_collider2 = std::get<BoxCollider>(data2.collider);
			collider1 = &box_collider1;
			collider2 = &box_collider2;

			// TODO: send with the collider info to this function because this is calculated previously
			// Get the current position of the collider
			Vector2 final_position1 = current_position(box_collider1,data1.transform,data1.rigidbody);
			Vector2 final_position2 = current_position(box_collider2,data2.transform,data2.rigidbody);

			// Determine move_back value for smallest overlap (x or y)
			move_back = box_box_collision_move_back(box_collider1,box_collider2,final_position1,final_position2);
			
		}
		else {
			// TODO: calcualte Box - Circle collision info
			const BoxCollider& box_collider = std::get<BoxCollider>(data1.collider);
			const CircleCollider& circle_collider = std::get<CircleCollider>(data2.collider);
			collider1 = &box_collider;
			collider2 = &circle_collider;
		}
	}
	else {
		if (std::holds_alternative<CircleCollider>(data2.collider)) {
			// TODO: calcualte Circle - Circle collision info
			const CircleCollider& circle_collider1 = std::get<CircleCollider>(data1.collider);
			const CircleCollider& circle_collider2 = std::get<CircleCollider>(data2.collider);
			collider1 = &circle_collider1;
			collider2 = &circle_collider2;
		}
		else {
			// TODO: calcualte Circle - Box collision info
			const CircleCollider& circle_collider = std::get<CircleCollider>(data1.collider);
			const BoxCollider& box_collider = std::get<BoxCollider>(data2.collider);
			collider1 = &circle_collider;
			collider2 = &box_collider;
		}
	}

	// One vaue is calculated for moving back. Calculate the other value (x or y) relateive to the move_back value.
	Direction move_back_direction = Direction::NONE;
	if(move_back.x != 0 && move_back.y > 0) {
		move_back_direction = Direction::BOTH;
	} else if (move_back.x != 0) {
		move_back_direction = Direction::X_DIRECTION;
		move_back.y = data1.rigidbody.data.linear_velocity.y * (move_back.x/data1.rigidbody.data.linear_velocity.x);
	} else if (move_back.y != 0) {
		move_back_direction = Direction::Y_DIRECTION;
		move_back.x = data1.rigidbody.data.linear_velocity.x * (move_back.y/data1.rigidbody.data.linear_velocity.y);
	}

	// collision info
	crepe::CollisionSystem::CollisionInfo collision_info{
            .first={ *collider1, data1.transform, data1.rigidbody },
            .second={ *collider2, data2.transform, data2.rigidbody },
						.move_back_value = move_back,
						.move_back_direction = move_back_direction,
        };

	// Determine if static needs to be called
	determine_collision_handler(collision_info);	
}


Vector2 CollisionSystem::box_box_collision_move_back(const BoxCollider& box_collider1,const BoxCollider& box_collider2,Vector2 final_position1,Vector2 final_position2)
{
	Vector2 resolution; // Default resolution vector
	Vector2 delta = final_position2 - final_position1;

	// Compute half-dimensions of the boxes
	double half_width1 = box_collider1.width / 2.0;
	double half_height1 = box_collider1.height / 2.0;
	double half_width2 = box_collider2.width / 2.0;
	double half_height2 = box_collider2.height / 2.0;

	// Calculate overlaps along X and Y axes
	double overlap_x = (half_width1 + half_width2) - std::abs(delta.x);
	double overlap_y = (half_height1 + half_height2) - std::abs(delta.y);

	// Check if there is a collision
	if (overlap_x > 0 && overlap_y > 0) {//should always be true check if this can be removed
		// Determine the direction of resolution
		if (overlap_x < overlap_y) {
			// Resolve along the X-axis (smallest overlap)
			resolution.x = (delta.x > 0) ? -overlap_x : overlap_x;
		} else if (overlap_y < overlap_x) {
			// Resolve along the Y-axis (smallest overlap)
			resolution.y = (delta.y > 0) ? -overlap_y : overlap_y;
		} else {
			// Equal overlap, resolve both directions with preference
			resolution.x = (delta.x > 0) ? -overlap_x : overlap_x;
			resolution.y = (delta.y > 0) ? -overlap_y : overlap_y;
		}
	}

	return resolution;
}

void CollisionSystem::determine_collision_handler(CollisionInfo& info){
	// Check rigidbody type for static
	if(info.first.rigidbody.data.body_type != Rigidbody::BodyType::STATIC)
	{
		// If second body is static perform the static collision handler in this system
		if(info.second.rigidbody.data.body_type == Rigidbody::BodyType::STATIC){
			static_collision_handler(info);
		}; 
		// Call collision event for user
		CollisionEvent data(info);
		EventManager::get_instance().trigger_event<CollisionEvent>(data, info.first.collider.game_object_id);
	}		
}

void CollisionSystem::static_collision_handler(CollisionInfo& info){
	// Move object back using calculate move back value 
	info.first.transform.position += info.move_back_value;

	// If bounce is enabled mirror velocity
	if(info.first.rigidbody.data.bounce) {
		if(info.move_back_direction == Direction::BOTH)
		{
			info.first.rigidbody.data.linear_velocity.y = -info.first.rigidbody.data.linear_velocity.y * info.first.rigidbody.data.elastisity;
			info.first.rigidbody.data.linear_velocity.x = -info.first.rigidbody.data.linear_velocity.x * info.first.rigidbody.data.elastisity;
		}
		else if(info.move_back_direction == Direction::Y_DIRECTION) {
			info.first.rigidbody.data.linear_velocity.y = -info.first.rigidbody.data.linear_velocity.y * info.first.rigidbody.data.elastisity;
		}
		else if(info.move_back_direction == Direction::X_DIRECTION){
			info.first.rigidbody.data.linear_velocity.x = -info.first.rigidbody.data.linear_velocity.x * info.first.rigidbody.data.elastisity;
		}
	}
	// Stop movement if bounce is disabled
	else {
		info.first.rigidbody.data.linear_velocity = {0,0};
	}
}

std::vector<std::pair<CollisionSystem::CollidedInfoStor,CollisionSystem::CollidedInfoStor>> CollisionSystem::check_collisions(const std::vector<std::reference_wrapper<BoxCollider>>& boxcolliders, const std::vector<std::reference_wrapper<CircleCollider>>& circlecolliders) {
	ComponentManager & mgr = this->component_manager;
	std::vector<std::pair<CollidedInfoStor,CollidedInfoStor>> collisions_ret;

	// TODO:
	// If no colliders skip
	// Check if colliders has rigidbody if not skip

	// TODO:
	// If amount is higer than lets say 16 for now use quadtree otwerwise skip
	// Quadtree code
	// Quadtree is placed over the input vector

	// Check collisions for each collider
	for (size_t i = 0; i < boxcolliders.size(); ++i) {
		// Fetch components for the first box collider
		if(!boxcolliders[i].get().active) continue;
		int game_object_id_1 = boxcolliders[i].get().game_object_id;
		Transform& transform1 = mgr.get_components_by_id<Transform>(game_object_id_1).front().get();
		if(!transform1.active) continue;
		Rigidbody& rigidbody1 = mgr.get_components_by_id<Rigidbody>(game_object_id_1).front().get();
		if(!rigidbody1.active) continue;
		
		// Check BoxCollider vs BoxCollider
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

	// Calculate half-extents (half width and half height)
	double half_width1 = box1.width / 2.0;
	double half_height1 = box1.height / 2.0;
	double half_width2 = box2.width / 2.0;
	double half_height2 = box2.height / 2.0;

	// Check if the boxes overlap along the X and Y axes
	return !(final_position1.x + half_width1 <= final_position2.x - half_width2 ||  // box1 is left of box2
						final_position1.x - half_width1 >= final_position2.x + half_width2 ||  // box1 is right of box2
						final_position1.y + half_height1 <= final_position2.y - half_height2 || // box1 is above box2
						final_position1.y - half_height1 >= final_position2.y + half_height2);  // box1 is below box2
}

bool CollisionSystem::check_box_circle_collision(const BoxCollider& box1, const CircleCollider& circle2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2) {
	// Get current positions of colliders
	Vector2 final_position1 = current_position(box1, transform1, rigidbody1);
	Vector2 final_position2 = current_position(circle2, transform2, rigidbody2);

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
