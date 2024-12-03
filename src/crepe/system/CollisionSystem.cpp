#include <cmath>
#include <algorithm>
#include <cstddef>
#include <functional>
#include <utility>
#include <variant>
#include <optional>

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
	
	std::vector<CollisionInternal> all_colliders;
	ComponentManager & mgr = this->component_manager;
	game_object_id_t id = 0;
	RefVector<Rigidbody> rigidbodies = mgr.get_components_by_type<Rigidbody>();
	for(Rigidbody& rigidbody : rigidbodies) {
		if (!rigidbody.active) continue;
		id = rigidbody.game_object_id;
		Transform& transform = this->component_manager.get_components_by_id<Transform>(id).front().get();
		RefVector<BoxCollider> boxcolliders	= mgr.get_components_by_type<BoxCollider>();
		for (BoxCollider& boxcollider : boxcolliders) {
			if(boxcollider.game_object_id != id) continue;
			if(!boxcollider.active) continue;
			all_colliders.push_back(
				{
					.id = id,
				  .collider = collider_variant{boxcollider},
					.transform = transform,
					.rigidbody = rigidbody
					}
				);
		}
		RefVector<CircleCollider> circlecolliders	= mgr.get_components_by_type<CircleCollider>();
		for (CircleCollider& circlecollider : circlecolliders) {
			if(circlecollider.game_object_id != id) continue;
			if(!circlecollider.active) continue;
			all_colliders.push_back(
				{
					.id = id,
				  .collider = collider_variant{circlecollider},
					.transform = transform,
					.rigidbody = rigidbody
					}
				);
		}
		 
	}

	// Check between all colliders if there is a collision
	std::vector<std::pair<CollisionInternal,CollisionInternal>> collided = gather_collisions(all_colliders);

	// For both objects call the collision handler 
	for (auto& collision_pair : collided) {
		collision_handler_request(collision_pair.first,collision_pair.second);
		collision_handler_request(collision_pair.second,collision_pair.first);
	}
}

void CollisionSystem::collision_handler_request(CollisionInternal& data1,CollisionInternal& data2){

	CollisionInternalType type = get_collider_type(data1.collider,data2.collider);
	std::pair<vec2,CollisionSystem::Direction> resolution_data = collision_handler(data1,data2,type);

	OptionalRef<Collider> collider1;
	OptionalRef<Collider> collider2;
	switch (type) {
		case CollisionInternalType::BOX_BOX:{
			collider1 = std::get<std::reference_wrapper<BoxCollider>>(data1.collider);
			collider2 = std::get<std::reference_wrapper<BoxCollider>>(data2.collider);
			break;
		}
		case CollisionInternalType::BOX_CIRCLE:{
			collider1 = std::get<std::reference_wrapper<BoxCollider>>(data1.collider);
			collider2 = std::get<std::reference_wrapper<CircleCollider>>(data2.collider);
			break;
		}
		case CollisionInternalType::CIRCLE_BOX:{
			collider1 = std::get<std::reference_wrapper<CircleCollider>>(data1.collider);
			collider2 = std::get<std::reference_wrapper<BoxCollider>>(data2.collider);
			break;
		}
		case CollisionInternalType::CIRCLE_CIRCLE:{
			collider1 = std::get<std::reference_wrapper<CircleCollider>>(data1.collider);
			collider2 = std::get<std::reference_wrapper<CircleCollider>>(data2.collider);
			break;
		}
	}
	
	// collision info
	crepe::CollisionSystem::CollisionInfo collision_info{
						.first_collider = collider1,
						.first_transform = data1.transform,
						.first_rigidbody = data1.rigidbody,
						.second_collider = collider2,
						.second_transform = data2.transform,
						.second_rigidbody = data2.rigidbody,
						.resolution = resolution_data.first,
						.resolution_direction = resolution_data.second,
        };

	// Determine if static needs to be called
	determine_collision_handler(collision_info);	
}


std::pair<vec2,CollisionSystem::Direction> CollisionSystem::collision_handler(CollisionInternal& data1,CollisionInternal& data2,CollisionInternalType type) {
	vec2 resolution;
	switch (type) {
		case CollisionInternalType::BOX_BOX:	{
			const BoxCollider & collider1 = std::get<std::reference_wrapper<BoxCollider>>(data1.collider);
			const BoxCollider & collider2 = std::get<std::reference_wrapper<BoxCollider>>(data2.collider);
			vec2 collider_pos1 = get_current_position(collider1.offset, data1.transform, data1.rigidbody);
			vec2 collider_pos2 = get_current_position(collider2.offset, data2.transform, data2.rigidbody);
			resolution = get_box_box_resolution(collider1,collider2,collider_pos1,collider_pos2);
			break;
		}
		case CollisionInternalType::BOX_CIRCLE: {
			const BoxCollider & collider1 = std::get<std::reference_wrapper<BoxCollider>>(data1.collider);
			const CircleCollider & collider2 = std::get<std::reference_wrapper<CircleCollider>>(data2.collider);
			vec2 collider_pos1 = get_current_position(collider1.offset, data1.transform, data1.rigidbody);
			vec2 collider_pos2 = get_current_position(collider2.offset, data2.transform, data2.rigidbody);
			resolution = get_circle_box_resolution(collider2,collider1,collider_pos2,collider_pos1);
			break;
		}
		case CollisionInternalType::CIRCLE_CIRCLE:	{
			const CircleCollider & collider1 = std::get<std::reference_wrapper<CircleCollider>>(data1.collider);
			const CircleCollider & collider2 = std::get<std::reference_wrapper<CircleCollider>>(data2.collider);
			vec2 collider_pos1 = get_current_position(collider1.offset, data1.transform, data1.rigidbody);
			vec2 collider_pos2 = get_current_position(collider2.offset, data2.transform, data2.rigidbody);
			resolution = get_circle_circle_resolution(collider1,collider2,collider_pos1,collider_pos2);
			break;
		}
		case CollisionInternalType::CIRCLE_BOX:	{
			const CircleCollider & collider1 = std::get<std::reference_wrapper<CircleCollider>>(data1.collider);
			const BoxCollider & collider2 = std::get<std::reference_wrapper<BoxCollider>>(data2.collider);
			vec2 collider_pos1 = get_current_position(collider1.offset, data1.transform, data1.rigidbody);
			vec2 collider_pos2 = get_current_position(collider2.offset, data2.transform, data2.rigidbody);
			resolution = get_circle_box_resolution(collider1,collider2,collider_pos1,collider_pos2);
			break;
		}
	}

	Direction resolution_direction = Direction::NONE;
	if(resolution.x != 0 && resolution.y > 0) {
		resolution_direction = Direction::BOTH;
	} else if (resolution.x != 0) {
		resolution_direction = Direction::X_DIRECTION;
		if(data1.rigidbody.data.linear_velocity.y != 0)	
		resolution.y = data1.rigidbody.data.linear_velocity.y * (resolution.x/data1.rigidbody.data.linear_velocity.x);
	} else if (resolution.y != 0) {
		resolution_direction = Direction::Y_DIRECTION;
		if(data1.rigidbody.data.linear_velocity.x != 0) 
		resolution.x = data1.rigidbody.data.linear_velocity.x * (resolution.y/data1.rigidbody.data.linear_velocity.y);
	}

	return std::make_pair(resolution,resolution_direction);
}

vec2 CollisionSystem::get_box_box_resolution(const BoxCollider& box_collider1,const BoxCollider& box_collider2,const vec2& final_position1,const vec2& final_position2) const
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

	// Check if there is a collision should always be true
	if (overlap_x > 0 && overlap_y > 0) {
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

vec2 CollisionSystem::get_circle_circle_resolution(const CircleCollider& circle_collider1, const CircleCollider& circle_collider2, const vec2& final_position1, const vec2& final_position2) const 
{
    vec2 delta = final_position2 - final_position1;

    // Compute the distance between the two circle centers
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);

    // Compute the combined radii of the two circles
    float combined_radius = circle_collider1.radius + circle_collider2.radius;

    // Compute the penetration depth
    float penetration_depth = combined_radius - distance;

    // Normalize the delta vector to get the collision direction
    vec2 collision_normal = delta / distance;

    // Compute the resolution vector
    vec2 resolution = collision_normal * penetration_depth;

    return resolution;
}

vec2 CollisionSystem::get_circle_box_resolution(const CircleCollider& circle_collider, const BoxCollider& box_collider, const vec2& circle_position, const vec2& box_position) const 
{
    vec2 delta = circle_position - box_position;

    // Compute half-dimensions of the box
    float half_width = box_collider.width / 2.0f;
    float half_height = box_collider.height / 2.0f;

    // Clamp circle center to the nearest point on the box
    vec2 closest_point;
    closest_point.x = std::clamp(delta.x, -half_width, half_width);
    closest_point.y = std::clamp(delta.y, -half_height, half_height);

    // Find the vector from the circle center to the closest point
    vec2 closest_delta = delta - closest_point;

    // Normalize the delta to get the collision direction
    float distance = std::sqrt(closest_delta.x * closest_delta.x + closest_delta.y * closest_delta.y);
    vec2 collision_normal = closest_delta / distance;

    // Compute penetration depth
    float penetration_depth = circle_collider.radius - distance;

    // Compute the resolution vector
    vec2 resolution = collision_normal * penetration_depth;

    return resolution;
}


void CollisionSystem::determine_collision_handler(CollisionInfo& info){
	// Check rigidbody type for static
	if(info.first_rigidbody.data.body_type == Rigidbody::BodyType::STATIC) return;
	// If second body is static perform the static collision handler in this system
	if(info.second_rigidbody.data.body_type == Rigidbody::BodyType::STATIC){
		static_collision_handler(info);
	}; 
	// Call collision event for user
	CollisionEvent data(info);
	EventManager::get_instance().trigger_event<CollisionEvent>(data, info.first_collider.game_object_id);
}

void CollisionSystem::static_collision_handler(CollisionInfo& info){
	// Move object back using calculate move back value 
	info.first_transform.position += info.resolution;

	// If bounce is enabled mirror velocity
	if(info.first_rigidbody.data.elastisity > 0) {
		if(info.resolution_direction == Direction::BOTH)
		{
			info.first_rigidbody.data.linear_velocity.y = -info.first_rigidbody.data.linear_velocity.y * info.first_rigidbody.data.elastisity;
			info.first_rigidbody.data.linear_velocity.x = -info.first_rigidbody.data.linear_velocity.x * info.first_rigidbody.data.elastisity;
		}
		else if(info.resolution_direction == Direction::Y_DIRECTION) {
			info.first_rigidbody.data.linear_velocity.y = -info.first_rigidbody.data.linear_velocity.y * info.first_rigidbody.data.elastisity;
		}
		else if(info.resolution_direction == Direction::X_DIRECTION){
			info.first_rigidbody.data.linear_velocity.x = -info.first_rigidbody.data.linear_velocity.x * info.first_rigidbody.data.elastisity;
		}
	}
	// Stop movement if bounce is disabled
	else {
		info.first_rigidbody.data.linear_velocity = {0,0};
	}
}

std::vector<std::pair<CollisionSystem::CollisionInternal,CollisionSystem::CollisionInternal>> CollisionSystem::gather_collisions(std::vector<CollisionInternal> & colliders) {
	
	
	// TODO:
	// If no colliders skip
	// Check if colliders has rigidbody if not skip

	// TODO:
	// If amount is higer than lets say 16 for now use quadtree otwerwise skip
	// Quadtree code
	// Quadtree is placed over the input vector

	// Return data of collided colliders which are variants
	std::vector<std::pair<CollisionInternal,CollisionInternal>> collisions_ret;
	//using visit to visit the variant to access the active and id.  
	for (size_t i = 0; i < colliders.size(); ++i) {
		for (size_t j = i + 1; j < colliders.size(); ++j) {
			if(colliders[i].id == colliders[j].id) continue;
				// Get collision type form variant colliders
				CollisionInternalType type = get_collider_type(colliders[i].collider,colliders[j].collider);
				if(!get_collision({
					.collider = colliders[i].collider,
					.transform = colliders[i].transform,
					.rigidbody = colliders[i].rigidbody,
					},
					{
					.collider = colliders[j].collider,
					.transform = colliders[j].transform,
					.rigidbody = colliders[j].rigidbody,
					},
					type)) continue;
				collisions_ret.emplace_back(colliders[i],colliders[j]);
		}
	}
	
	return collisions_ret;
}

std::optional<std::pair<std::reference_wrapper<Transform>, std::reference_wrapper<Rigidbody>>>
CollisionSystem::get_active_transform_and_rigidbody(game_object_id_t game_object_id) const{
    RefVector<Transform> transforms = this->component_manager.get_components_by_id<Transform>(game_object_id);
    if (transforms.empty()) return std::nullopt;

		Transform& transform = transforms.front().get();
    if (!transform.active) return std::nullopt;

    RefVector<Rigidbody> rigidbodies = this->component_manager.get_components_by_id<Rigidbody>(game_object_id);
    if (rigidbodies.empty()) return std::nullopt;

    Rigidbody& rigidbody = rigidbodies.front().get();
    if (!rigidbody.active) return std::nullopt;

    // Return the active components
    return std::make_pair(std::ref(transform), std::ref(rigidbody));
}

CollisionSystem::CollisionInternalType CollisionSystem::get_collider_type(const collider_variant& collider1,const collider_variant& collider2) const{
	if(std::holds_alternative<std::reference_wrapper<CircleCollider>>(collider1)){
		if(std::holds_alternative<std::reference_wrapper<CircleCollider>>(collider2))
		{
			return CollisionInternalType::CIRCLE_CIRCLE;
		}
		else {
			return CollisionInternalType::CIRCLE_BOX;
		}
	}
	else {
		if(std::holds_alternative<std::reference_wrapper<CircleCollider>>(collider2))
		{
			return CollisionInternalType::BOX_CIRCLE;
		}
		else {
			return CollisionInternalType::BOX_BOX;
		}
	}
}

bool CollisionSystem::get_collision(const CollisionInternal& first_info,const CollisionInternal& second_info, CollisionInternalType type) const{
	switch (type) {
		case CollisionInternalType::BOX_BOX:	{
			const BoxCollider & box_collider1 = std::get<std::reference_wrapper<BoxCollider>>(first_info.collider);
			const BoxCollider & box_collider2 = std::get<std::reference_wrapper<BoxCollider>>(second_info.collider);
			return get_box_box_collision(box_collider1,box_collider2,first_info.transform,second_info.transform,second_info.rigidbody,second_info.rigidbody);
		}
		case CollisionInternalType::BOX_CIRCLE: {
			const BoxCollider & box_collider = std::get<std::reference_wrapper<BoxCollider>>(first_info.collider);
			const CircleCollider & circle_collider = std::get<std::reference_wrapper<CircleCollider>>(second_info.collider);
			return get_box_circle_collision(box_collider,circle_collider,first_info.transform,second_info.transform,second_info.rigidbody,second_info.rigidbody);
		}
		case CollisionInternalType::CIRCLE_CIRCLE:	{
			const CircleCollider & circle_collider1 = std::get<std::reference_wrapper<CircleCollider>>(first_info.collider);
			const CircleCollider & circle_collider2 = std::get<std::reference_wrapper<CircleCollider>>(second_info.collider);
			return get_circle_circle_collision(circle_collider1,circle_collider2,first_info.transform,second_info.transform,second_info.rigidbody,second_info.rigidbody);
		}
		case CollisionInternalType::CIRCLE_BOX:	{
			const CircleCollider & circle_collider = std::get<std::reference_wrapper<CircleCollider>>(first_info.collider);
			const BoxCollider & box_collider = std::get<std::reference_wrapper<BoxCollider>>(second_info.collider);
			return get_box_circle_collision(box_collider,circle_collider,first_info.transform,second_info.transform,second_info.rigidbody,second_info.rigidbody);
		}
	}
	return false;
}


bool CollisionSystem::get_box_box_collision(const BoxCollider& box1, const BoxCollider& box2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2) const
{
	// Get current positions of colliders
	vec2 final_position1 = get_current_position(box1.offset,transform1,rigidbody1);
	vec2 final_position2 = get_current_position(box2.offset,transform2,rigidbody2);

	// Calculate half-extents (half width and half height)
	float half_width1 = box1.width / 2.0;
	float half_height1 = box1.height / 2.0;
	float half_width2 = box2.width / 2.0;
	float half_height2 = box2.height / 2.0;

	// Check if the boxes overlap along the X and Y axes
	return (final_position1.x + half_width1 > final_position2.x - half_width2 &&  // not left
        final_position1.x - half_width1 < final_position2.x + half_width2 &&  // not right
        final_position1.y + half_height1 > final_position2.y - half_height2 && // not above
        final_position1.y - half_height1 < final_position2.y + half_height2);  // not below
}

bool CollisionSystem::get_box_circle_collision(const BoxCollider& box1, const CircleCollider& circle2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2) const {
	// Get current positions of colliders
	vec2 final_position1 = get_current_position(box1.offset, transform1, rigidbody1);
	vec2 final_position2 = get_current_position(circle2.offset, transform2, rigidbody2);

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

bool CollisionSystem::get_circle_circle_collision(const CircleCollider& circle1, const CircleCollider& circle2, const Transform& transform1, const Transform& transform2, const Rigidbody& rigidbody1, const Rigidbody& rigidbody2) const {
	// Get current positions of colliders
	vec2 final_position1 = get_current_position(circle1.offset,transform1,rigidbody1);
	vec2 final_position2 = get_current_position(circle2.offset,transform2,rigidbody2);

	float distance_x = final_position1.x - final_position2.x;
	float distance_y = final_position1.y - final_position2.y;
	float distance_squared = distance_x * distance_x + distance_y * distance_y;

	// Calculate the sum of the radii
	float radius_sum = circle1.radius + circle2.radius;

	// Check if the distance between the centers is less than or equal to the sum of the radii
	return distance_squared <= radius_sum * radius_sum;
}

vec2 CollisionSystem::get_current_position(const vec2& collider_offset, const Transform& transform, const Rigidbody& rigidbody) const {
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
