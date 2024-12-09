#include <algorithm>
#include <cmath>

#include "api/LoopTimer.h"
#include "api/Rigidbody.h"
#include "api/Transform.h"
#include "manager/ComponentManager.h"
#include "manager/Mediator.h"

#include "AISystem.h"
#include "types.h"

using namespace crepe;

void AISystem::update() {
	const Mediator & mediator = this->mediator;
	ComponentManager & mgr = mediator.component_manager;
	RefVector<AI> ai_components = mgr.get_components_by_type<AI>();

	//TODO: Use fixed loop dt (this is not available at master at the moment)
	double dt = LoopTimer::get_instance().get_delta_time();

	// Loop through all AI components
	for (AI & ai : ai_components) {
		if (!ai.active) {
			continue;
		}

		RefVector<Rigidbody> rigidbodies
			= mgr.get_components_by_id<Rigidbody>(ai.game_object_id);
		Rigidbody & rigidbody = rigidbodies.front().get();

		// Calculate the force to apply to the entity
		vec2 force = this->calculate(ai);
		// Calculate the acceleration (using the above calculated force)
		vec2 acceleration = force / rigidbody.data.mass;
		// Finally, update Rigidbody's velocity
		rigidbody.data.linear_velocity += acceleration * dt;
	}
}

vec2 AISystem::calculate(AI & ai) {
	vec2 force;

	// Run all the behaviors that are on, and stop if the force gets too high
	if (ai.on(AI::BehaviorType::FLEE)) {
		vec2 force_to_add = this->flee(ai);

		if (!this->accumulate_force(ai, force, force_to_add)) {
			return force;
		}
	}
	if (ai.on(AI::BehaviorType::ARRIVE)) {
		vec2 force_to_add = this->arrive(ai);

		if (!this->accumulate_force(ai, force, force_to_add)) {
			return force;
		}
	}
	if (ai.on(AI::BehaviorType::SEEK)) {
		vec2 force_to_add = this->seek(ai);

		if (!this->accumulate_force(ai, force, force_to_add)) {
			return force;
		}
	}
	if (ai.on(AI::BehaviorType::PATH_FOLLOW)) {
		vec2 force_to_add = this->path_follow(ai);

		if (!this->accumulate_force(ai, force, force_to_add)) {
			return force;
		}
	}

	return force;
}

bool AISystem::accumulate_force(AI & ai, vec2 & running_total, vec2 force_to_add) {
	float magnitude = running_total.length();
	float magnitude_remaining = ai.max_force - magnitude;

	if (magnitude_remaining <= 0.0f) {
		// If the force is already at/above the max force, return false
		return false;
	}

	float magnitude_to_add = force_to_add.length();
	if (magnitude_to_add < magnitude_remaining) {
		// If the force to add is less than the remaining force, add it
		running_total += force_to_add;
	} else {
		// If the force to add is greater than the remaining force, add a fraction of it
		force_to_add.normalize();
		running_total += force_to_add * magnitude_remaining;
	}

	return true;
}

vec2 AISystem::seek(const AI & ai) {
	const Mediator & mediator = this->mediator;
	ComponentManager & mgr = mediator.component_manager;
	RefVector<Transform> transforms = mgr.get_components_by_id<Transform>(ai.game_object_id);
	Transform & transform = transforms.front().get();
	RefVector<Rigidbody> rigidbodies = mgr.get_components_by_id<Rigidbody>(ai.game_object_id);
	Rigidbody & rigidbody = rigidbodies.front().get();

	// Calculate the desired velocity
	vec2 desired_velocity = ai.seek_target - transform.position;
	desired_velocity.normalize();
	desired_velocity *= rigidbody.data.max_linear_velocity;

	return desired_velocity - rigidbody.data.linear_velocity;
}

vec2 AISystem::flee(const AI & ai) {
	const Mediator & mediator = this->mediator;
	ComponentManager & mgr = mediator.component_manager;
	RefVector<Transform> transforms = mgr.get_components_by_id<Transform>(ai.game_object_id);
	Transform & transform = transforms.front().get();
	RefVector<Rigidbody> rigidbodies = mgr.get_components_by_id<Rigidbody>(ai.game_object_id);
	Rigidbody & rigidbody = rigidbodies.front().get();

	// Calculate the desired velocity if the entity is within the panic distance
	vec2 desired_velocity = transform.position - ai.flee_target;
	if (desired_velocity.length_squared() > ai.square_flee_panic_distance) {
		return vec2{0, 0};
	}
	desired_velocity.normalize();
	desired_velocity *= rigidbody.data.max_linear_velocity;

	return desired_velocity - rigidbody.data.linear_velocity;
}

vec2 AISystem::arrive(const AI & ai) {
	const Mediator & mediator = this->mediator;
	ComponentManager & mgr = mediator.component_manager;
	RefVector<Transform> transforms = mgr.get_components_by_id<Transform>(ai.game_object_id);
	Transform & transform = transforms.front().get();
	RefVector<Rigidbody> rigidbodies = mgr.get_components_by_id<Rigidbody>(ai.game_object_id);
	Rigidbody & rigidbody = rigidbodies.front().get();

	// Calculate the desired velocity (taking into account the deceleration rate)
	vec2 to_target = ai.seek_target - transform.position;
	float distance = to_target.length();
	if (distance > 0.0f) {
		float speed = distance / ai.arrive_deceleration;
		speed = std::min(speed, rigidbody.data.max_linear_velocity.length());
		vec2 desired_velocity = to_target * (speed / distance);

		return desired_velocity - rigidbody.data.linear_velocity;
	}

	return vec2{0, 0};
}

vec2 AISystem::path_follow(AI & ai) {
	const Mediator & mediator = this->mediator;
	ComponentManager & mgr = mediator.component_manager;
	RefVector<Transform> transforms = mgr.get_components_by_id<Transform>(ai.game_object_id);
	Transform & transform = transforms.front().get();
	RefVector<Rigidbody> rigidbodies = mgr.get_components_by_id<Rigidbody>(ai.game_object_id);
	Rigidbody & rigidbody = rigidbodies.front().get();

	if (ai.path.empty()) {
		return vec2{0, 0};
	}

	// Get the target node
	vec2 target = ai.path.at(ai.path_index);
	// Calculate the force to apply to the entity
	vec2 to_target = target - transform.position;
	if (to_target.length_squared() > ai.path_node_distance * ai.path_node_distance) {
		// If the entity is not close enough to the target node, seek it
		ai.seek_target = target;
	} else {
		// If the entity is close enough to the target node, move to the next node
		ai.path_index++;
		if (ai.path_index >= ai.path.size()) {
			if (ai.path_loop) {
				// If the path is looping, reset the path index
				ai.path_index = 0;
			} else {
				// If the path is not looping, arrive at the last node
				ai.path_index = ai.path.size() - 1;
				return this->arrive(ai);
			}
		}
	}

	// Seek the target node
	return this->seek(ai);
}
