#include <algorithm>
#include <cmath>
#include <cstddef>
#include <functional>
#include <optional>
#include <utility>
#include <variant>

#include "../manager/ComponentManager.h"
#include "../manager/EventManager.h"
#include "api/BoxCollider.h"
#include "api/CircleCollider.h"
#include "api/Event.h"
#include "api/Metadata.h"
#include "api/Rigidbody.h"
#include "api/Transform.h"
#include "api/Vector2.h"

#include "Collider.h"
#include "CollisionSystem.h"
#include "types.h"
#include "util/OptionalRef.h"

using namespace crepe;

void CollisionSystem::update() {
	std::vector<CollisionInternal> all_colliders;
	game_object_id_t id = 0;
	ComponentManager & mgr = this->mediator.component_manager;
	RefVector<Rigidbody> rigidbodies = mgr.get_components_by_type<Rigidbody>();
	// Collisions can only happen on object with a rigidbody
	for (Rigidbody & rigidbody : rigidbodies) {
		if (!rigidbody.active) continue;
		id = rigidbody.game_object_id;
		Transform & transform = mgr.get_components_by_id<Transform>(id).front().get();
		// Check if the boxcollider is active and has the same id as the rigidbody.
		RefVector<BoxCollider> boxcolliders = mgr.get_components_by_type<BoxCollider>();
		for (BoxCollider & boxcollider : boxcolliders) {
			if (boxcollider.game_object_id != id) continue;
			if (!boxcollider.active) continue;
			all_colliders.push_back({.id = id,
									 .collider = collider_variant{boxcollider},
									 .transform = transform,
									 .rigidbody = rigidbody});
		}
		// Check if the circlecollider is active and has the same id as the rigidbody.
		RefVector<CircleCollider> circlecolliders
			= mgr.get_components_by_type<CircleCollider>();
		for (CircleCollider & circlecollider : circlecolliders) {
			if (circlecollider.game_object_id != id) continue;
			if (!circlecollider.active) continue;
			all_colliders.push_back({.id = id,
									 .collider = collider_variant{circlecollider},
									 .transform = transform,
									 .rigidbody = rigidbody});
		}
	}

	// Check between all colliders if there is a collision
	std::vector<std::pair<CollisionInternal, CollisionInternal>> collided
		= this->gather_collisions(all_colliders);

	// For both objects call the collision handler
	for (auto & collision_pair : collided) {
		this->collision_handler_request(collision_pair.first, collision_pair.second);
		this->collision_handler_request(collision_pair.second, collision_pair.first);
	}
}

void CollisionSystem::collision_handler_request(CollisionInternal & this_data,
												CollisionInternal & other_data) {

	CollisionInternalType type
		= this->get_collider_type(this_data.collider, other_data.collider);
	std::pair<vec2, CollisionSystem::Direction> resolution_data
		= this->collision_handler(this_data, other_data, type);
	ComponentManager & mgr = this->mediator.component_manager;
	OptionalRef<Metadata> this_metadata
		= mgr.get_components_by_id<Metadata>(this_data.id).front().get();
	OptionalRef<Metadata> other_metadata
		= mgr.get_components_by_id<Metadata>(other_data.id).front().get();
	OptionalRef<Collider> this_collider;
	OptionalRef<Collider> other_collider;
	switch (type) {
		case CollisionInternalType::BOX_BOX: {
			this_collider = std::get<std::reference_wrapper<BoxCollider>>(this_data.collider);
			other_collider
				= std::get<std::reference_wrapper<BoxCollider>>(other_data.collider);
			break;
		}
		case CollisionInternalType::BOX_CIRCLE: {
			this_collider = std::get<std::reference_wrapper<BoxCollider>>(this_data.collider);
			other_collider
				= std::get<std::reference_wrapper<CircleCollider>>(other_data.collider);
			break;
		}
		case CollisionInternalType::CIRCLE_BOX: {
			this_collider
				= std::get<std::reference_wrapper<CircleCollider>>(this_data.collider);
			other_collider
				= std::get<std::reference_wrapper<BoxCollider>>(other_data.collider);
			break;
		}
		case CollisionInternalType::CIRCLE_CIRCLE: {
			this_collider
				= std::get<std::reference_wrapper<CircleCollider>>(this_data.collider);
			other_collider
				= std::get<std::reference_wrapper<CircleCollider>>(other_data.collider);
			break;
		}
	}

	// collision info
	crepe::CollisionSystem::CollisionInfo collision_info{
		.this_collider = this_collider,
		.this_transform = this_data.transform,
		.this_rigidbody = this_data.rigidbody,
		.this_metadata = this_metadata,
		.other_collider = other_collider,
		.other_transform = other_data.transform,
		.other_rigidbody = other_data.rigidbody,
		.other_metadata = other_metadata,
		.resolution = resolution_data.first,
		.resolution_direction = resolution_data.second,
	};

	// Determine if static needs to be called
	this->determine_collision_handler(collision_info);
}

std::pair<vec2, CollisionSystem::Direction>
CollisionSystem::collision_handler(CollisionInternal & data1, CollisionInternal & data2,
								   CollisionInternalType type) {
	vec2 resolution;
	switch (type) {
		case CollisionInternalType::BOX_BOX: {
			const BoxCollider & collider1
				= std::get<std::reference_wrapper<BoxCollider>>(data1.collider);
			const BoxCollider & collider2
				= std::get<std::reference_wrapper<BoxCollider>>(data2.collider);
			vec2 collider_pos1 = this->get_current_position(collider1.offset, data1.transform,
															data1.rigidbody);
			vec2 collider_pos2 = this->get_current_position(collider2.offset, data2.transform,
															data2.rigidbody);
			resolution = this->get_box_box_resolution(collider1, collider2, collider_pos1,
													  collider_pos2);
			break;
		}
		case CollisionInternalType::BOX_CIRCLE: {
			const BoxCollider & collider1
				= std::get<std::reference_wrapper<BoxCollider>>(data1.collider);
			const CircleCollider & collider2
				= std::get<std::reference_wrapper<CircleCollider>>(data2.collider);
			vec2 collider_pos1 = this->get_current_position(collider1.offset, data1.transform,
															data1.rigidbody);
			vec2 collider_pos2 = this->get_current_position(collider2.offset, data2.transform,
															data2.rigidbody);
			resolution = -this->get_circle_box_resolution(collider2, collider1, collider_pos2,
														  collider_pos1);
			break;
		}
		case CollisionInternalType::CIRCLE_CIRCLE: {
			const CircleCollider & collider1
				= std::get<std::reference_wrapper<CircleCollider>>(data1.collider);
			const CircleCollider & collider2
				= std::get<std::reference_wrapper<CircleCollider>>(data2.collider);
			vec2 collider_pos1 = this->get_current_position(collider1.offset, data1.transform,
															data1.rigidbody);
			vec2 collider_pos2 = this->get_current_position(collider2.offset, data2.transform,
															data2.rigidbody);
			resolution = this->get_circle_circle_resolution(collider1, collider2,
															collider_pos1, collider_pos2);
			break;
		}
		case CollisionInternalType::CIRCLE_BOX: {
			const CircleCollider & collider1
				= std::get<std::reference_wrapper<CircleCollider>>(data1.collider);
			const BoxCollider & collider2
				= std::get<std::reference_wrapper<BoxCollider>>(data2.collider);
			vec2 collider_pos1 = this->get_current_position(collider1.offset, data1.transform,
															data1.rigidbody);
			vec2 collider_pos2 = this->get_current_position(collider2.offset, data2.transform,
															data2.rigidbody);
			resolution = this->get_circle_box_resolution(collider1, collider2, collider_pos1,
														 collider_pos2);
			break;
		}
	}

	Direction resolution_direction = Direction::NONE;
	if (resolution.x != 0 && resolution.y != 0) {
		resolution_direction = Direction::BOTH;
	} else if (resolution.x != 0) {
		resolution_direction = Direction::X_DIRECTION;
		if (data1.rigidbody.data.linear_velocity.y != 0)
			resolution.y = data1.rigidbody.data.linear_velocity.y
						   * (resolution.x / data1.rigidbody.data.linear_velocity.x);
	} else if (resolution.y != 0) {
		resolution_direction = Direction::Y_DIRECTION;
		if (data1.rigidbody.data.linear_velocity.x != 0)
			resolution.x = data1.rigidbody.data.linear_velocity.x
						   * (resolution.y / data1.rigidbody.data.linear_velocity.y);
	}

	return std::make_pair(resolution, resolution_direction);
}

vec2 CollisionSystem::get_box_box_resolution(const BoxCollider & box_collider1,
											 const BoxCollider & box_collider2,
											 const vec2 & final_position1,
											 const vec2 & final_position2) const {
	vec2 resolution; // Default resolution vector
	vec2 delta = final_position2 - final_position1;

	// Compute half-dimensions of the boxes
	float half_width1 = box_collider1.dimensions.x / 2.0;
	float half_height1 = box_collider1.dimensions.y / 2.0;
	float half_width2 = box_collider2.dimensions.x / 2.0;
	float half_height2 = box_collider2.dimensions.y / 2.0;

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

vec2 CollisionSystem::get_circle_circle_resolution(const CircleCollider & circle_collider1,
												   const CircleCollider & circle_collider2,
												   const vec2 & final_position1,
												   const vec2 & final_position2) const {
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
	vec2 resolution = -collision_normal * penetration_depth;

	return resolution;
}

vec2 CollisionSystem::get_circle_box_resolution(const CircleCollider & circle_collider,
												const BoxCollider & box_collider,
												const vec2 & circle_position,
												const vec2 & box_position) const {
	vec2 delta = circle_position - box_position;

	// Compute half-dimensions of the box
	float half_width = box_collider.dimensions.x / 2.0f;
	float half_height = box_collider.dimensions.y / 2.0f;

	// Clamp circle center to the nearest point on the box
	vec2 closest_point;
	closest_point.x = std::clamp(delta.x, -half_width, half_width);
	closest_point.y = std::clamp(delta.y, -half_height, half_height);

	// Find the vector from the circle center to the closest point
	vec2 closest_delta = delta - closest_point;

	// Normalize the delta to get the collision direction
	float distance
		= std::sqrt(closest_delta.x * closest_delta.x + closest_delta.y * closest_delta.y);
	vec2 collision_normal = closest_delta / distance;

	// Compute penetration depth
	float penetration_depth = circle_collider.radius - distance;
	
	// Compute the resolution vector
	vec2 resolution = collision_normal * penetration_depth;

	return resolution;
}

void CollisionSystem::determine_collision_handler(CollisionInfo & info) {
	// Check rigidbody type for static
	if (info.this_rigidbody.data.body_type == Rigidbody::BodyType::STATIC) return;
	// If second body is static perform the static collision handler in this system
	if (info.other_rigidbody.data.body_type == Rigidbody::BodyType::STATIC) {
		this->static_collision_handler(info);
	};
	// Call collision event for user
	CollisionEvent data(info);
	EventManager & emgr = this->mediator.event_manager;
	emgr.trigger_event<CollisionEvent>(data, info.this_collider.game_object_id);
}

void CollisionSystem::static_collision_handler(CollisionInfo & info) {
	// Move object back using calculate move back value
	info.this_transform.position += info.resolution;

	// If bounce is enabled mirror velocity
	if (info.this_rigidbody.data.elastisity_coefficient > 0) {
		if (info.resolution_direction == Direction::BOTH) {
			info.this_rigidbody.data.linear_velocity.y
				= -info.this_rigidbody.data.linear_velocity.y
				  * info.this_rigidbody.data.elastisity_coefficient;
			info.this_rigidbody.data.linear_velocity.x
				= -info.this_rigidbody.data.linear_velocity.x
				  * info.this_rigidbody.data.elastisity_coefficient;
		} else if (info.resolution_direction == Direction::Y_DIRECTION) {
			info.this_rigidbody.data.linear_velocity.y
				= -info.this_rigidbody.data.linear_velocity.y
				  * info.this_rigidbody.data.elastisity_coefficient;
		} else if (info.resolution_direction == Direction::X_DIRECTION) {
			info.this_rigidbody.data.linear_velocity.x
				= -info.this_rigidbody.data.linear_velocity.x
				  * info.this_rigidbody.data.elastisity_coefficient;
		}
	}
	// Stop movement if bounce is disabled
	else {
		info.this_rigidbody.data.linear_velocity = {0, 0};
	}
}

std::vector<std::pair<CollisionSystem::CollisionInternal, CollisionSystem::CollisionInternal>>
CollisionSystem::gather_collisions(std::vector<CollisionInternal> & colliders) {

	// TODO:
	// If no colliders skip
	// Check if colliders has rigidbody if not skip

	// TODO:
	// If amount is higer than lets say 16 for now use quadtree otwerwise skip
	// Quadtree code
	// Quadtree is placed over the input vector

	// Return data of collided colliders which are variants
	std::vector<std::pair<CollisionInternal, CollisionInternal>> collisions_ret;
	//using visit to visit the variant to access the active and id.
	for (size_t i = 0; i < colliders.size(); ++i) {
		for (size_t j = i + 1; j < colliders.size(); ++j) {
			if (colliders[i].id == colliders[j].id) continue;
			if (!have_common_layer(colliders[i].rigidbody.data.collision_layers,
								   colliders[j].rigidbody.data.collision_layers))
				continue;
			CollisionInternalType type
				= get_collider_type(colliders[i].collider, colliders[j].collider);
			if (!get_collision(
					{
						.collider = colliders[i].collider,
						.transform = colliders[i].transform,
						.rigidbody = colliders[i].rigidbody,
					},
					{
						.collider = colliders[j].collider,
						.transform = colliders[j].transform,
						.rigidbody = colliders[j].rigidbody,
					},
					type))
				continue;
			collisions_ret.emplace_back(colliders[i], colliders[j]);
		}
	}

	return collisions_ret;
}

bool CollisionSystem::have_common_layer(const std::set<int> & layers1,
										const std::set<int> & layers2) {

	// Check if any number is equal in the layers
	for (int num : layers1) {
		if (layers2.contains(num)) {
			// Common layer found
			return true;
			break;
		}
	}
	// No common layer found
	return false;
}

CollisionSystem::CollisionInternalType
CollisionSystem::get_collider_type(const collider_variant & collider1,
								   const collider_variant & collider2) const {
	if (std::holds_alternative<std::reference_wrapper<CircleCollider>>(collider1)) {
		if (std::holds_alternative<std::reference_wrapper<CircleCollider>>(collider2)) {
			return CollisionInternalType::CIRCLE_CIRCLE;
		} else {
			return CollisionInternalType::CIRCLE_BOX;
		}
	} else {
		if (std::holds_alternative<std::reference_wrapper<CircleCollider>>(collider2)) {
			return CollisionInternalType::BOX_CIRCLE;
		} else {
			return CollisionInternalType::BOX_BOX;
		}
	}
}

bool CollisionSystem::get_collision(const CollisionInternal & first_info,
									const CollisionInternal & second_info,
									CollisionInternalType type) const {
	switch (type) {
		case CollisionInternalType::BOX_BOX: {
			const BoxCollider & box_collider1
				= std::get<std::reference_wrapper<BoxCollider>>(first_info.collider);
			const BoxCollider & box_collider2
				= std::get<std::reference_wrapper<BoxCollider>>(second_info.collider);
			return this->get_box_box_collision(box_collider1, box_collider2,
											   first_info.transform, second_info.transform,
											   second_info.rigidbody, second_info.rigidbody);
		}
		case CollisionInternalType::BOX_CIRCLE: {
			const BoxCollider & box_collider
				= std::get<std::reference_wrapper<BoxCollider>>(first_info.collider);
			const CircleCollider & circle_collider
				= std::get<std::reference_wrapper<CircleCollider>>(second_info.collider);
			return this->get_box_circle_collision(
				box_collider, circle_collider, first_info.transform, second_info.transform,
				second_info.rigidbody, second_info.rigidbody);
		}
		case CollisionInternalType::CIRCLE_CIRCLE: {
			const CircleCollider & circle_collider1
				= std::get<std::reference_wrapper<CircleCollider>>(first_info.collider);
			const CircleCollider & circle_collider2
				= std::get<std::reference_wrapper<CircleCollider>>(second_info.collider);
			return this->get_circle_circle_collision(
				circle_collider1, circle_collider2, first_info.transform,
				second_info.transform, second_info.rigidbody, second_info.rigidbody);
		}
		case CollisionInternalType::CIRCLE_BOX: {
			const CircleCollider & circle_collider
				= std::get<std::reference_wrapper<CircleCollider>>(first_info.collider);
			const BoxCollider & box_collider
				= std::get<std::reference_wrapper<BoxCollider>>(second_info.collider);
			return this->get_box_circle_collision(
				box_collider, circle_collider, first_info.transform, second_info.transform,
				second_info.rigidbody, second_info.rigidbody);
		}
	}
	return false;
}

bool CollisionSystem::get_box_box_collision(const BoxCollider & box1, const BoxCollider & box2,
											const Transform & transform1,
											const Transform & transform2,
											const Rigidbody & rigidbody1,
											const Rigidbody & rigidbody2) const {
	// Get current positions of colliders
	vec2 final_position1 = this->get_current_position(box1.offset, transform1, rigidbody1);
	vec2 final_position2 = this->get_current_position(box2.offset, transform2, rigidbody2);

	// Calculate half-extents (half width and half height)
	float half_width1 = box1.dimensions.x / 2.0;
	float half_height1 = box1.dimensions.y / 2.0;
	float half_width2 = box2.dimensions.x / 2.0;
	float half_height2 = box2.dimensions.y / 2.0;

	// Check if the boxes overlap along the X and Y axes
	return (final_position1.x + half_width1 > final_position2.x - half_width2
			&& final_position1.x - half_width1 < final_position2.x + half_width2
			&& final_position1.y + half_height1 > final_position2.y - half_height2
			&& final_position1.y - half_height1 < final_position2.y + half_height2);
}

bool CollisionSystem::get_box_circle_collision(const BoxCollider & box1,
											   const CircleCollider & circle2,
											   const Transform & transform1,
											   const Transform & transform2,
											   const Rigidbody & rigidbody1,
											   const Rigidbody & rigidbody2) const {
	// Get current positions of colliders
	vec2 final_position1 = this->get_current_position(box1.offset, transform1, rigidbody1);
	vec2 final_position2 = this->get_current_position(circle2.offset, transform2, rigidbody2);

	// Calculate box half-extents
	float half_width = box1.dimensions.x / 2.0;
	float half_height = box1.dimensions.y / 2.0;

	// Find the closest point on the box to the circle's center
	float closest_x = std::max(final_position1.x - half_width,
							   std::min(final_position2.x, final_position1.x + half_width));
	float closest_y = std::max(final_position1.y - half_height,
							   std::min(final_position2.y, final_position1.y + half_height));

	// Calculate the distance squared between the circle's center and the closest point on the box
	float distance_x = final_position2.x - closest_x;
	float distance_y = final_position2.y - closest_y;
	float distance_squared = distance_x * distance_x + distance_y * distance_y;

	// Compare distance squared with the square of the circle's radius
	return distance_squared < circle2.radius * circle2.radius;
}

bool CollisionSystem::get_circle_circle_collision(const CircleCollider & circle1,
												  const CircleCollider & circle2,
												  const Transform & transform1,
												  const Transform & transform2,
												  const Rigidbody & rigidbody1,
												  const Rigidbody & rigidbody2) const {
	// Get current positions of colliders
	vec2 final_position1 = this->get_current_position(circle1.offset, transform1, rigidbody1);
	vec2 final_position2 = this->get_current_position(circle2.offset, transform2, rigidbody2);

	float distance_x = final_position1.x - final_position2.x;
	float distance_y = final_position1.y - final_position2.y;
	float distance_squared = distance_x * distance_x + distance_y * distance_y;

	// Calculate the sum of the radii
	float radius_sum = circle1.radius + circle2.radius;

	// Check if the distance between the centers is less than or equal to the sum of the radii
	return distance_squared < radius_sum * radius_sum;
}

vec2 CollisionSystem::get_current_position(const vec2 & collider_offset,
										   const Transform & transform,
										   const Rigidbody & rigidbody) const {
	// Get the rotation in radians
	float radians1 = transform.rotation * (M_PI / 180.0);

	// Calculate total offset with scale
	vec2 total_offset = (rigidbody.data.offset + collider_offset) * transform.scale;

	// Rotate
	float rotated_total_offset_x1
		= total_offset.x * cos(radians1) - total_offset.y * sin(radians1);
	float rotated_total_offset_y1
		= total_offset.x * sin(radians1) + total_offset.y * cos(radians1);

	// Final positions considering scaling and rotation
	return (transform.position + vec2(rotated_total_offset_x1, rotated_total_offset_y1));
}
