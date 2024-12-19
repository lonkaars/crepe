#include <algorithm>
#include <cmath>
#include <cstddef>
#include <emmintrin.h>
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
#include "util/AbsolutePosition.h"
#include "util/OptionalRef.h"

#include "CollisionSystem.h"
#include "types.h"

using namespace crepe;
using enum Rigidbody::BodyType;

CollisionSystem::CollisionInfo CollisionSystem::CollisionInfo::operator-() const {
  return {
    .self = this->other,
		.other = this->self,
		.resolution = -this->resolution,
		.resolution_direction = this->resolution_direction,
  };
}

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
		Metadata & metadata = mgr.get_components_by_id<Metadata>(id).front().get();
		// Check if the boxcollider is active and has the same id as the rigidbody.
		RefVector<BoxCollider> boxcolliders = mgr.get_components_by_type<BoxCollider>();
		for (BoxCollider & boxcollider : boxcolliders) {
			if (boxcollider.game_object_id != id) continue;
			if (!boxcollider.active) continue;
			all_colliders.push_back({.id = id,
									 .collider = collider_variant{boxcollider},
									 .info = {transform,rigidbody, metadata}
									 });
		}
		// Check if the circlecollider is active and has the same id as the rigidbody.
		RefVector<CircleCollider> circlecolliders
			= mgr.get_components_by_type<CircleCollider>();
		for (CircleCollider & circlecollider : circlecolliders) {
			if (circlecollider.game_object_id != id) continue;
			if (!circlecollider.active) continue;
			all_colliders.push_back({.id = id,
									 .collider = collider_variant{circlecollider},
									 .info = {transform,rigidbody, metadata}
									 });
		}
	}

	// Check between all colliders if there is a collision (collision handling)
	std::vector<std::pair<CollisionInternal, CollisionInternal>> collided
		= this->gather_collisions(all_colliders);

	// For the object convert the info and call the collision handler if needed
	for (auto & collision_pair : collided) {
		// Convert internal struct to external struct
		CollisionInfo info = this->get_collision_info(collision_pair.first, collision_pair.second);
		// Determine if and/or what collison handler is needed.
		this->determine_collision_handler(info);
	}
}

// Below is for collision detection 
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
			if (!should_collide(colliders[i], colliders[j])) continue;
				CollisionInternalType type = get_collider_type(colliders[i].collider, colliders[j].collider);
			if (!detect_collision(colliders[i],colliders[j],type)) continue;
				//fet 
				collisions_ret.emplace_back(colliders[i], colliders[j]);
		}
	}
	return collisions_ret;
}


bool CollisionSystem::should_collide(const CollisionInternal & self, const CollisionInternal & other) const{

	const Rigidbody::Data & self_rigidbody = self.info.rigidbody.data;
	const Rigidbody::Data & other_rigidbody = other.info.rigidbody.data;
	const Metadata & self_metadata = self.info.metadata;
	const Metadata & other_metadata = other.info.metadata;

	// Check collision layers
	if(self_rigidbody.collision_layers.contains(other_rigidbody.collision_layer)) return true;
	if(other_rigidbody.collision_layers.contains(self_rigidbody.collision_layer)) return true;

	// Check names
	if(self_rigidbody.collision_names.contains(other_metadata.name)) return true;
	if(other_rigidbody.collision_names.contains(self_metadata.name)) return true;

	// Check tags
	if(self_rigidbody.collision_tags.contains(other_metadata.tag)) return true;
	if(other_rigidbody.collision_tags.contains(self_metadata.tag)) return true;

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

bool CollisionSystem::detect_collision(CollisionInternal & self,CollisionInternal & other,const CollisionInternalType & type) {
	vec2 resolution;
	switch (type) {
		case CollisionInternalType::BOX_BOX: { 
			// Box-Box collision detection
			const BoxColliderInternal BOX1 = {
				.collider = std::get<std::reference_wrapper<BoxCollider>>(self.collider),
				.transform = self.info.transform,
				.rigidbody = self.info.rigidbody
			};
			const BoxColliderInternal BOX2 = {
				.collider = std::get<std::reference_wrapper<BoxCollider>>(other.collider),
				.transform = other.info.transform,
				.rigidbody = other.info.rigidbody
			};
			// Get resolution vector from box-box collision detection
			resolution = this->get_box_box_detection(BOX1, BOX2);
			// If no collision (NaN values), return false
			if(std::isnan(resolution.x) && std::isnan(resolution.y)) return false;
			break;
			
		}
		case CollisionInternalType::BOX_CIRCLE: {
			// Box-Circle collision detection
			const BoxColliderInternal BOX1 = {
				.collider = std::get<std::reference_wrapper<BoxCollider>>(self.collider),
				.transform = self.info.transform,
				.rigidbody = self.info.rigidbody
			};
			const CircleColliderInternal CIRCLE2 = {
				.collider = std::get<std::reference_wrapper<CircleCollider>>(other.collider),
				.transform = other.info.transform,
				.rigidbody = other.info.rigidbody
			};
			// Get resolution vector from box-circle collision detection
			resolution = this->get_box_circle_detection(BOX1, CIRCLE2);
			// If no collision (NaN values), return false
			if(std::isnan(resolution.x) && std::isnan(resolution.y)) return false;
			// Invert the resolution vector for proper collision response
			resolution = -resolution;
			break;
		}
		case CollisionInternalType::CIRCLE_CIRCLE: { 
			// Circle-Circle collision detection
			const CircleColliderInternal CIRCLE1 = {
				.collider = std::get<std::reference_wrapper<CircleCollider>>(self.collider),
				.transform = self.info.transform,
				.rigidbody = self.info.rigidbody
			};
			const CircleColliderInternal CIRCLE2 = {
				.collider = std::get<std::reference_wrapper<CircleCollider>>(other.collider),
				.transform = other.info.transform,
				.rigidbody = other.info.rigidbody
			};
			// Get resolution vector from circle-circle collision detection
			resolution = this->get_circle_circle_detection(CIRCLE1,CIRCLE2);
			// If no collision (NaN values), return false
			if(std::isnan(resolution.x) && std::isnan(resolution.y)) return false;
			break;
		}
		case CollisionInternalType::CIRCLE_BOX: { 
			// Circle-Box collision detection
			const CircleColliderInternal CIRCLE1 = {
				.collider = std::get<std::reference_wrapper<CircleCollider>>(self.collider),
				.transform = self.info.transform,
				.rigidbody = self.info.rigidbody
			};
			const BoxColliderInternal BOX2 = {
				.collider = std::get<std::reference_wrapper<BoxCollider>>(other.collider),
				.transform = other.info.transform,
				.rigidbody = other.info.rigidbody
			};
			// Get resolution vector from box-circle collision detection (order swapped)
			resolution = this->get_box_circle_detection(BOX2, CIRCLE1);
			// If no collision (NaN values), return false
			if(std::isnan(resolution.x) && std::isnan(resolution.y)) return false;
			break;
		}
		case CollisionInternalType::NONE:
		// No collision detection needed if the type is NONE
		return false;
		break;
	}
	 // Store the calculated resolution vector for the 'self' collider
	self.resolution = resolution;
	// Calculate the resolution direction based on the rigidbody data
	self.resolution_direction = this->resolution_correction(self.resolution, self.info.rigidbody.data);
	// For the 'other' collider, the resolution is the opposite direction of 'self'
	other.resolution = -self.resolution;
	other.resolution_direction = self.resolution_direction;

	// Return true if a collision was detected and resolution was calculated
	return true;
}

vec2 CollisionSystem::get_box_box_detection(const BoxColliderInternal & box1, const BoxColliderInternal & box2) const {
	vec2 resolution{std::nanf(""), std::nanf("")};
	// Get current positions of colliders
	vec2 pos1  = AbsolutePosition::get_position(box1.transform, box1.collider.offset);
	vec2 pos2  = AbsolutePosition::get_position(box2.transform, box2.collider.offset);

	// Scale dimensions
	vec2 scaled_box1 = box1.collider.dimensions * box1.transform.scale;
	vec2 scaled_box2 = box2.collider.dimensions * box2.transform.scale;
	vec2 delta = pos2 - pos1;


	// Calculate half-extents (half width and half height)
	float half_width1 = scaled_box1.x / 2.0;
	float half_height1 = scaled_box1.y / 2.0;
	float half_width2 = scaled_box2.x / 2.0;
	float half_height2 = scaled_box2.y / 2.0;

	if (pos1.x + half_width1 > pos2.x - half_width2
			&& pos1.x - half_width1 < pos2.x + half_width2
			&& pos1.y + half_height1 > pos2.y - half_height2
			&& pos1.y - half_height1 < pos2.y + half_height2)
	{
		resolution = {0,0};
		float overlap_x = (half_width1 + half_width2) - std::abs(delta.x);
		float overlap_y = (half_height1 + half_height2) - std::abs(delta.y);
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
	}
	return resolution;
}

vec2 CollisionSystem::get_box_circle_detection(const BoxColliderInternal & box, const CircleColliderInternal & circle) const {
	/// Get current positions of colliders
    vec2 box_pos = AbsolutePosition::get_position(box.transform, box.collider.offset);
    vec2 circle_pos = AbsolutePosition::get_position(circle.transform, circle.collider.offset);

    // Scale dimensions
    vec2 scaled_box = box.collider.dimensions * box.transform.scale;
    float scaled_circle_radius = circle.collider.radius * circle.transform.scale;

    // Calculate box half-extents
    float half_width = scaled_box.x / 2.0f;
    float half_height = scaled_box.y / 2.0f;

    // Find the closest point on the box to the circle's center
    float closest_x = std::max(box_pos.x - half_width, std::min(circle_pos.x, box_pos.x + half_width));
		float closest_y = std::max(box_pos.y - half_height, std::min(circle_pos.y, box_pos.y + half_height));
    
		float distance_x = circle_pos.x - closest_x;
		float distance_y = circle_pos.y - closest_y;
		float distance_squared = distance_x * distance_x + distance_y * distance_y;
		if(distance_squared < scaled_circle_radius * scaled_circle_radius){
			vec2 delta = circle_pos - box_pos;

			// Clamp circle center to the nearest point on the box
			vec2 closest_point;
			closest_point.x = std::clamp(delta.x, -half_width, half_width);
			closest_point.y = std::clamp(delta.y, -half_height, half_height);

			// Find the vector from the circle center to the closest point
			vec2 closest_delta = delta - closest_point;

			float distance = std::sqrt(closest_delta.x * closest_delta.x + closest_delta.y * closest_delta.y);
			vec2 collision_normal = closest_delta / distance;

			// Compute penetration depth
			float penetration_depth = scaled_circle_radius - distance;

			// Compute the resolution vector
			return vec2{collision_normal * penetration_depth};
		}
    // No collision
    return vec2{std::nanf(""), std::nanf("")};
}

vec2 CollisionSystem::get_circle_circle_detection(const CircleColliderInternal & circle1, const CircleColliderInternal & circle2) const {
	// Get current positions of colliders
	vec2 final_position1 = AbsolutePosition::get_position(circle1.transform, circle1.collider.offset);
	vec2 final_position2 = AbsolutePosition::get_position(circle2.transform, circle2.collider.offset);

	// Scale dimensions
	float scaled_circle1 = circle1.collider.radius * circle1.transform.scale;
	float scaled_circle2 = circle2.collider.radius * circle2.transform.scale;

	float distance_x = final_position1.x - final_position2.x;
	float distance_y = final_position1.y - final_position2.y;
	float distance_squared = distance_x * distance_x + distance_y * distance_y;

	// Calculate the sum of the radii
	float radius_sum = scaled_circle1 + scaled_circle2;

	// Check for collision (distance squared must be less than the square of the radius sum)
	if (distance_squared < radius_sum * radius_sum) {
		vec2 delta = final_position2 - final_position1;

		// Compute the distance between the two circle centers
		float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);

		// Compute the combined radii of the two circles
		float combined_radius = scaled_circle1 + scaled_circle2;

		// Compute the penetration depth
		float penetration_depth = combined_radius - distance;

		// Normalize the delta vector to get the collision direction
		vec2 collision_normal = delta / distance;

		// Compute the resolution vector
		vec2 resolution = -collision_normal * penetration_depth;

		return resolution;
	}
	// No collision
	return vec2{std::nanf(""), std::nanf("")};
}

CollisionSystem::Direction CollisionSystem::resolution_correction(vec2 & resolution,const Rigidbody::Data & rigidbody) {

	// Calculate the other value to move back correctly
	// If only X or Y has a value determine what is should be to move back.
	Direction resolution_direction = Direction::NONE;
	// If both are not zero a perfect corner has been hit
	if (resolution.x != 0 && resolution.y != 0) {
		resolution_direction = Direction::BOTH;
	// If x is not zero a horizontal action was latest action.
	} else if (resolution.x != 0) {
		resolution_direction = Direction::X_DIRECTION;
		// If both are 0 resolution y should not be changed (y_velocity can be 0 by kinematic object movement)
		if (rigidbody.linear_velocity.x != 0 && rigidbody.linear_velocity.y != 0)
			resolution.y = -rigidbody.linear_velocity.y * (resolution.x / rigidbody.linear_velocity.x);
	} else if (resolution.y != 0) {
		resolution_direction = Direction::Y_DIRECTION;
		// If both are 0 resolution x should not be changed (x_velocity can be 0 by kinematic object movement)
		if (rigidbody.linear_velocity.x != 0 && rigidbody.linear_velocity.y != 0)
			resolution.x = -rigidbody.linear_velocity.x * (resolution.y / rigidbody.linear_velocity.y);
	}

	return resolution_direction;
}

CollisionSystem::CollisionInfo CollisionSystem::get_collision_info(const CollisionInternal & in_self, const CollisionInternal & in_other) const{

	crepe::CollisionSystem::ColliderInfo self {
	.transform = in_self.info.transform,
	.rigidbody = in_self.info.rigidbody,
	.metadata = in_self.info.metadata,
	};

	crepe::CollisionSystem::ColliderInfo other {
	.transform = in_other.info.transform,
	.rigidbody = in_other.info.rigidbody,
	.metadata = in_other.info.metadata,
	};

	struct CollisionInfo collision_info{
		.self = self,
		.other = other,
		.resolution = in_self.resolution,
		.resolution_direction = in_self.resolution_direction,
	};
	return collision_info;
}

void CollisionSystem::determine_collision_handler(const CollisionInfo & info) {
	Rigidbody::BodyType self_type =	info.self.rigidbody.data.body_type;
	Rigidbody::BodyType other_type =	info.other.rigidbody.data.body_type;
	bool self_kinematic = info.self.rigidbody.data.kinematic_collision;
	bool other_kinematic = info.other.rigidbody.data.kinematic_collision;
	// Inverted collision info
	CollisionInfo inverted = -info;
	// If both objects are static skip handle call collision script
	if (self_type == STATIC
		&& other_type == STATIC)
		return;

	//	First body is not dynamic
	if (self_type != DYNAMIC) {
		bool static_collision = self_type == STATIC && other_type == DYNAMIC;
		bool kinematic_collision = self_type == KINEMATIC && other_type == DYNAMIC && self_kinematic;

		// Handle collision 
		if (static_collision || kinematic_collision) this->static_collision_handler(inverted);
		// Call scripts
		this->call_collision_events(inverted);
		return;
	}

	// Second body is not dynamic
	if (other_type != DYNAMIC) {
		bool static_collision = other_type == STATIC;
		bool kinematic_collision = other_type == KINEMATIC && other_kinematic;
		// Handle collision 
		if (static_collision || kinematic_collision) this->static_collision_handler(info);
		// Call scripts
		this->call_collision_events(info);
		return;
	}

	// Dynamic
	// Handle collision 
	this->dynamic_collision_handler(info);
	// Call scripts
	this->call_collision_events(info);
}

void CollisionSystem::static_collision_handler(const CollisionInfo & info) {
	
	vec2 & transform_pos = info.self.transform.position;
	float elasticity = info.self.rigidbody.data.elasticity_coefficient;
	vec2 & rigidbody_vel = info.self.rigidbody.data.linear_velocity;
	
	// Move object back using calculate move back value
	transform_pos += info.resolution;

	switch (info.resolution_direction) {
		case Direction::BOTH:
			//bounce
			if (elasticity > 0) {
				rigidbody_vel = -rigidbody_vel * elasticity;
			}
			//stop movement
			else {
				rigidbody_vel = {0, 0};
			}
			break;
		case Direction::Y_DIRECTION:
			// Bounce
			if (elasticity > 0) {
				rigidbody_vel.y = -rigidbody_vel.y * elasticity;
			}
			// Stop movement
			else {
				rigidbody_vel.y = 0;
				transform_pos.x -= info.resolution.x;
			}
			break;
		case Direction::X_DIRECTION:
			// Bounce
			if (elasticity > 0) {
				rigidbody_vel.x = -rigidbody_vel.x * elasticity;
			}
			// Stop movement
			else {
				rigidbody_vel.x = 0;
				transform_pos.y -= info.resolution.y;
			}
			break;
		case Direction::NONE:
			// Not possible
			break;
	}
}

void CollisionSystem::dynamic_collision_handler(const CollisionInfo & info) {

	vec2 & self_transform_pos = info.self.transform.position;
	vec2 & other_transform_pos = info.other.transform.position;
	float self_elasticity = info.self.rigidbody.data.elasticity_coefficient;
	float other_elasticity = info.other.rigidbody.data.elasticity_coefficient;
	vec2 & self_rigidbody_vel = info.self.rigidbody.data.linear_velocity;
	vec2 & other_rigidbody_vel = info.other.rigidbody.data.linear_velocity;

	self_transform_pos += info.resolution / 2;
	other_transform_pos += -(info.resolution / 2);

	switch (info.resolution_direction) {
		case Direction::BOTH:
			if (self_elasticity > 0) {
				self_rigidbody_vel = -self_rigidbody_vel * self_elasticity;
			} else {
				self_rigidbody_vel = {0, 0};
			}

			if (other_elasticity > 0) {
				other_rigidbody_vel = -other_rigidbody_vel * other_elasticity;
			} else {
				other_rigidbody_vel = {0, 0};
			}
			break;
		case Direction::Y_DIRECTION:
			if (self_elasticity > 0) {
				self_rigidbody_vel.y = -self_rigidbody_vel.y * self_elasticity;
			}
			// Stop movement
			else {
				self_rigidbody_vel.y = 0;
				self_transform_pos.x -= info.resolution.x;
			}

			if (other_elasticity > 0) {
				other_rigidbody_vel.y = -other_rigidbody_vel.y * other_elasticity;
			}
			// Stop movement
			else {
				other_rigidbody_vel.y = 0;
				other_transform_pos.x -= info.resolution.x;
			}
			break;
		case Direction::X_DIRECTION:
			if (self_elasticity > 0) {
				self_rigidbody_vel.x = -self_rigidbody_vel.x * self_elasticity;
			}
			// Stop movement
			else {
				self_rigidbody_vel.x = 0;
				self_transform_pos.y -= info.resolution.y;
			}

			if (other_elasticity > 0) {
				other_rigidbody_vel.x = -other_rigidbody_vel.x * other_elasticity;
			}
			// Stop movement
			else {
				other_rigidbody_vel.x = 0;
				other_transform_pos.y -= info.resolution.y;
			}
			break;
		case Direction::NONE:
			// Not possible
			break;
	}
}

void CollisionSystem::call_collision_events(const CollisionInfo & info) {
	CollisionEvent data(info);
	CollisionEvent data_inverted(-info);
	EventManager & emgr = this->mediator.event_manager;
	emgr.trigger_event<CollisionEvent>(data, info.self.transform.game_object_id);
	emgr.trigger_event<CollisionEvent>(data_inverted,
									   -info.self.transform.game_object_id);
}




