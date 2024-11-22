#include <cmath>
#include <algorithm>
#include <cstddef>
#include <functional>
#include <utility>
#include <variant>
#include <optional>
#include <tuple>

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
#include "types.h"
#include "util/OptionalRef.h"

using namespace crepe;

void CollisionSystem::update() {
	// Get collider components and keep them seperate
	ComponentManager & mgr = this->component_manager;
	std::vector<std::reference_wrapper<BoxCollider>> boxcolliders	= mgr.get_components_by_type<BoxCollider>();
	std::vector<std::reference_wrapper<CircleCollider>> circlecolliders	= mgr.get_components_by_type<CircleCollider>();

	std::vector<collider_stor> all_colliders;
	// Add BoxCollider references
	for (auto& box : boxcolliders) {
			all_colliders.push_back(collider_stor{box});
	}

	// Add CircleCollider references
	for (auto& circle : circlecolliders) {
			all_colliders.push_back(collider_stor{circle});
	}
	
	// Check between all colliders if there is a collision
	std::vector<std::pair<CollidedInfoStor,CollidedInfoStor>> collided = check_collisions(all_colliders);

	// For both objects call the collision handler 
	for (auto& collision_pair : collided) {
		collision_handler_request(collision_pair.first,collision_pair.second);
		collision_handler_request(collision_pair.second,collision_pair.first);
	}
}

void CollisionSystem::collision_handler_request(CollidedInfoStor& data1,CollidedInfoStor& data2){

	ColliderStorType type = check_collider_type(data1.collider,data2.collider);
	std::pair<vec2,CollisionSystem::Direction> move_back_data = collision_handler(data1,data2,type);

	OptionalRef<Collider> collider1;
	OptionalRef<Collider> collider2;
	switch (type) {
		case ColliderStorType::BOX_BOX:{
			collider1 = std::get<std::reference_wrapper<BoxCollider>>(data1.collider);
			collider2 = std::get<std::reference_wrapper<BoxCollider>>(data2.collider);
		}
		case ColliderStorType::BOX_CIRCLE:{
			collider1 = std::get<std::reference_wrapper<BoxCollider>>(data1.collider);
			collider2 = std::get<std::reference_wrapper<CircleCollider>>(data2.collider);
		}
		case ColliderStorType::CIRCLE_BOX:{
			collider1 = std::get<std::reference_wrapper<CircleCollider>>(data1.collider);
			collider2 = std::get<std::reference_wrapper<BoxCollider>>(data2.collider);
		}
		case ColliderStorType::CIRCLE_CIRCLE:{
			collider1 = std::get<std::reference_wrapper<CircleCollider>>(data1.collider);
			collider2 = std::get<std::reference_wrapper<CircleCollider>>(data2.collider);
		}
	}
	
	// collision info
	crepe::CollisionSystem::CollisionInfo collision_info{
            .first={ collider1, data1.transform, data1.rigidbody },
            .second={ collider2, data2.transform, data2.rigidbody },
						.move_back_value = move_back_data.first,
						.move_back_direction = move_back_data.second,
        };

	// Determine if static needs to be called
	determine_collision_handler(collision_info);	
}


std::pair<vec2,CollisionSystem::Direction> CollisionSystem::collision_handler(CollidedInfoStor& data1,CollidedInfoStor& data2,ColliderStorType type) {
	vec2 move_back;
	switch (type) {
		case ColliderStorType::BOX_BOX:	{
			const BoxCollider & collider1 = std::get<std::reference_wrapper<BoxCollider>>(data1.collider);
			const BoxCollider & collider2 = std::get<std::reference_wrapper<BoxCollider>>(data2.collider);
			vec2 collider_pos1 = current_position(collider1.offset, data1.transform, data1.rigidbody);
			vec2 collider_pos2 = current_position(collider2.offset, data2.transform, data2.rigidbody);
			move_back = box_box_move_back(collider1,collider2,collider_pos1,collider_pos2);
		}
		case ColliderStorType::BOX_CIRCLE: {
		
		}
		case ColliderStorType::CIRCLE_CIRCLE:	{
		
		}
		case ColliderStorType::CIRCLE_BOX:	{
		
		}
	}

	Direction move_back_direction = Direction::NONE;
	if(move_back.x != 0 && move_back.y > 0) {
		move_back_direction = Direction::BOTH;
	} else if (move_back.x != 0) {
		move_back_direction = Direction::X_DIRECTION;
		if(data1.rigidbody.data.linear_velocity.y != 0)	
		move_back.y = data1.rigidbody.data.linear_velocity.y * (move_back.x/data1.rigidbody.data.linear_velocity.x);
	} else if (move_back.y != 0) {
		move_back_direction = Direction::Y_DIRECTION;
		if(data1.rigidbody.data.linear_velocity.x != 0) 
		move_back.x = data1.rigidbody.data.linear_velocity.x * (move_back.y/data1.rigidbody.data.linear_velocity.y);
	}

	return {move_back,move_back_direction};
}

vec2 CollisionSystem::box_box_move_back(const BoxCollider& box_collider1,const BoxCollider& box_collider2,vec2 final_position1,vec2 final_position2)
{
	vec2 resolution; // Default resolution vector
	vec2 delta = final_position2 - final_position1;

	// Compute half-dimensions of the boxes
	float half_width1 = box_collider1.width / 2.0;
	float half_height1 = box_collider1.height / 2.0;
	float half_width2 = box_collider2.width / 2.0;
	float half_height2 = box_collider2.height / 2.0;

	// Calculate overlaps along X and Y axes
	float overlap_x = (half_width1 + half_width2) - std::abs(delta.x);
	float overlap_y = (half_height1 + half_height2) - std::abs(delta.y);

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

std::vector<std::pair<CollisionSystem::CollidedInfoStor,CollisionSystem::CollidedInfoStor>> CollisionSystem::check_collisions(std::vector<collider_stor> & colliders) {
	
	
	// TODO:
	// If no colliders skip
	// Check if colliders has rigidbody if not skip

	// TODO:
	// If amount is higer than lets say 16 for now use quadtree otwerwise skip
	// Quadtree code
	// Quadtree is placed over the input vector

	// Function to retrieve active transform and rigidbody components for a given game_object_id
	auto get_active_transform_and_rigidbody = [&](game_object_id_t game_object_id) 
	-> std::optional<std::pair<std::reference_wrapper<Transform>, std::reference_wrapper<Rigidbody>>> {
		RefVector<Transform> transforms = this->component_manager.get_components_by_id<Transform>(game_object_id);
		if (transforms.empty()) return std::nullopt;

		RefVector<Rigidbody> rigidbodies = this->component_manager.get_components_by_id<Rigidbody>(game_object_id);
		if (rigidbodies.empty()) return std::nullopt;

		Transform& transform = transforms.front().get();
		if (!transform.active) return std::nullopt;

		Rigidbody& rigidbody = rigidbodies.front().get();
		if (!rigidbody.active) return std::nullopt;

		// Return the active components
		return std::make_pair(std::ref(transform), std::ref(rigidbody));
    };
	

	std::vector<std::pair<CollidedInfoStor,CollidedInfoStor>> collisions_ret;
	for (size_t i = 0; i < colliders.size(); ++i) {
    std::visit([&](auto& inner_collider_ref) {
			if (inner_collider_ref.get().active) return;
			auto inner_components = get_active_transform_and_rigidbody(inner_collider_ref.get().game_object_id);
			if (inner_components) return;
			for (size_t j = i + 1; j < colliders.size(); ++j) {
				std::visit([&](auto& outer_collider_ref) { 
					if (outer_collider_ref.get().active) return;
					if (inner_collider_ref.get().game_object_id == outer_collider_ref.get().game_object_id) return;
					auto outer_components = get_active_transform_and_rigidbody(inner_collider_ref.get().game_object_id);
					if (outer_components) return;
					ColliderStorType type = check_collider_type(colliders[i],colliders[j]);
					check_collision(colliders[i],*inner_components,colliders[j],*outer_components,type);
					collisions_ret.emplace_back(
                        CollidedInfoStor{colliders[i], inner_components->first.get(), inner_components->second.get()},
                        CollidedInfoStor{colliders[j], outer_components->first.get(), outer_components->second.get()}
                    );
				}, colliders[j]);
			}
    }, colliders[i]);
	}
	
	return collisions_ret;
}

CollisionSystem::ColliderStorType CollisionSystem::check_collider_type(const collider_stor& collider1,const collider_stor& collider2){
	if(std::holds_alternative<std::reference_wrapper<CircleCollider>>(collider1)){
		if(std::holds_alternative<std::reference_wrapper<CircleCollider>>(collider2))
		{
			return ColliderStorType::CIRCLE_CIRCLE;
		}
		else {
			return ColliderStorType::CIRCLE_BOX;
		}
	}
	else {
		if(std::holds_alternative<std::reference_wrapper<CircleCollider>>(collider2))
		{
			return ColliderStorType::BOX_CIRCLE;
		}
		else {
			return ColliderStorType::BOX_BOX;
		}
	}
}

bool CollisionSystem::check_collision(const collider_stor& collider1,std::pair<std::reference_wrapper<Transform>, std::reference_wrapper<Rigidbody>> components1,const collider_stor& collider2,std::pair<std::reference_wrapper<Transform>, std::reference_wrapper<Rigidbody>> components2, ColliderStorType type){
	switch (type) {
		case ColliderStorType::BOX_BOX:	{
			const BoxCollider & box_collider1 = std::get<std::reference_wrapper<BoxCollider>>(collider1);
			const BoxCollider & box_collider2 = std::get<std::reference_wrapper<BoxCollider>>(collider2);
			return check_box_box_collision(box_collider1,box_collider2,components1.first.get(),components2.first.get(),components1.second.get(),components2.second.get());
		}
		case ColliderStorType::BOX_CIRCLE: {
			const BoxCollider & box_collider = std::get<std::reference_wrapper<BoxCollider>>(collider1);
			const CircleCollider & circle_collider = std::get<std::reference_wrapper<CircleCollider>>(collider2);
			return check_box_circle_collision(box_collider,circle_collider,components1.first.get(),components2.first.get(),components1.second.get(),components2.second.get());
		}
		case ColliderStorType::CIRCLE_CIRCLE:	{
			const CircleCollider & circle_collider1 = std::get<std::reference_wrapper<CircleCollider>>(collider1);
			const CircleCollider & circle_collider2 = std::get<std::reference_wrapper<CircleCollider>>(collider2);
			return check_circle_circle_collision(circle_collider1,circle_collider2,components1.first.get(),components2.first.get(),components1.second.get(),components2.second.get());
		}
		case ColliderStorType::CIRCLE_BOX:	{
			const BoxCollider & box_collider = std::get<std::reference_wrapper<BoxCollider>>(collider1);
			const CircleCollider & circle_collider = std::get<std::reference_wrapper<CircleCollider>>(collider2);
			return check_box_circle_collision(box_collider,circle_collider,components1.first.get(),components2.first.get(),components1.second.get(),components2.second.get());
		}
	}
}


bool CollisionSystem::check_box_box_collision(const BoxCollider& box1, const BoxCollider& box2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2)
{
	// Get current positions of colliders
	vec2 final_position1 = current_position(box1.offset,transform1,rigidbody1);
	vec2 final_position2 = current_position(box2.offset,transform2,rigidbody2);

	// Calculate half-extents (half width and half height)
	float half_width1 = box1.width / 2.0;
	float half_height1 = box1.height / 2.0;
	float half_width2 = box2.width / 2.0;
	float half_height2 = box2.height / 2.0;

	// Check if the boxes overlap along the X and Y axes
	return !(final_position1.x + half_width1 <= final_position2.x - half_width2 ||  // box1 is left of box2
						final_position1.x - half_width1 >= final_position2.x + half_width2 ||  // box1 is right of box2
						final_position1.y + half_height1 <= final_position2.y - half_height2 || // box1 is above box2
						final_position1.y - half_height1 >= final_position2.y + half_height2);  // box1 is below box2
}

bool CollisionSystem::check_box_circle_collision(const BoxCollider& box1, const CircleCollider& circle2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2) {
	// Get current positions of colliders
	vec2 final_position1 = current_position(box1.offset, transform1, rigidbody1);
	vec2 final_position2 = current_position(circle2.offset, transform2, rigidbody2);

	// Calculate box half-extents
	float half_width = box1.width / 2.0;
	float half_height = box1.height / 2.0;

	// Find the closest point on the box to the circle's center
	float closest_x = std::max(final_position1.x - half_width, std::min(final_position2.x, final_position1.x + half_width));
	float closest_y = std::max(final_position1.y - half_height, std::min(final_position2.y, final_position1.y + half_height));

	// Calculate the distance squared between the circle's center and the closest point on the box
	float distance_x = final_position2.x - closest_x;
	float distance_y = final_position2.y - closest_y;
	float distance_squared = distance_x * distance_x + distance_y * distance_y;

	// Compare distance squared with the square of the circle's radius
	return distance_squared <= circle2.radius * circle2.radius;
}

bool CollisionSystem::check_circle_circle_collision(const CircleCollider& circle1, const CircleCollider& circle2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2) {
	// Get current positions of colliders
	vec2 final_position1 = current_position(circle1.offset,transform1,rigidbody1);
	vec2 final_position2 = current_position(circle2.offset,transform2,rigidbody2);

	float distance_x = final_position1.x - final_position2.x;
	float distance_y = final_position1.y - final_position2.y;
	float distance_squared = distance_x * distance_x + distance_y * distance_y;

	// Calculate the sum of the radii
	float radius_sum = circle1.radius + circle2.radius;

	// Check if the distance between the centers is less than or equal to the sum of the radii
	return distance_squared <= radius_sum * radius_sum;
}

vec2 CollisionSystem::current_position(vec2 collider_offset, const Transform& transform, const Rigidbody& rigidbody) {
	// Get the rotation in radians
	float radians1 = transform.rotation * (M_PI / 180.0);

	// Calculate total offset with scale
	vec2 total_offset = (rigidbody.data.offset + collider_offset) * transform.scale;

	// Rotate
	float rotated_total_offset_x1 = total_offset.x * cos(radians1) - total_offset.y * sin(radians1);
	float rotated_total_offset_y1 = total_offset.x * sin(radians1) + total_offset.y * cos(radians1);

	// Final positions considering scaling and rotation
	return(transform.position + vec2(rotated_total_offset_x1, rotated_total_offset_y1));

}
