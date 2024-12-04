#include "../ComponentManager.h"
#include "api/LoopTimer.h"
#include "api/Transform.h"
#include "types.h"

#include "AISystem.h"

using namespace crepe;

void AISystem::update() {
	ComponentManager & mgr = this->component_manager;
	RefVector<AI> ai_components = mgr.get_components_by_type<AI>();

	double dt = LoopTimer::get_instance().get_delta_time();

	for (AI & ai : ai_components) {
		vec2 force = this->calculate(ai);
		vec2 acceleration = force / ai.mass;
		ai.velocity += acceleration * dt;
		ai.velocity.truncate(ai.max_speed);

		// Update the position
		RefVector<Transform> transforms
			= mgr.get_components_by_id<Transform>(ai.game_object_id);
		Transform & transform = transforms.front().get();
		transform.position += ai.velocity * dt;
	}
}

vec2 AISystem::calculate(AI & ai) {
	vec2 force;

	if (ai.on(AI::BehaviorType::SEEK)) {
		vec2 force_to_add = this->seek(ai);

		if (!this->accumulate_force(force, force_to_add)) {
			return force;
		}
	}
	if (ai.on(AI::BehaviorType::FLEE)) {
		// Flee from the target
	}
	if (ai.on(AI::BehaviorType::ARRIVE)) {
		// Arrive at the target
	}
	if (ai.on(AI::BehaviorType::PATH_FOLLOW)) {
		// Follow the path
	}

	return force;
}

bool AISystem::accumulate_force(vec2 & running_total, vec2 force_to_add) {
	double magnitude_remaining = running_total.length();
	double magnitude_to_add = force_to_add.length();

	if (magnitude_remaining + magnitude_to_add > 0) {
		running_total += force_to_add;
		return true;
	}

	return false;
}

vec2 AISystem::seek(const AI & ai) {
	ComponentManager & mgr = this->component_manager;
	RefVector<Transform> transforms = mgr.get_components_by_id<Transform>(ai.game_object_id);
	Transform & transform = transforms.front().get();

	vec2 desired_velocity = ai.seek_target - transform.position;
	desired_velocity.normalize();
	desired_velocity *= ai.max_speed;

	return desired_velocity - ai.velocity;
}
