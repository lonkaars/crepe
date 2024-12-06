#include "api/LoopTimer.h"
#include "api/Rigidbody.h"
#include "api/Transform.h"
#include "manager/ComponentManager.h"
#include "manager/Mediator.h"
#include "types.h"

#include "AISystem.h"

using namespace crepe;

void AISystem::update() {
	const Mediator & mediator = this->mediator;
	ComponentManager & mgr = mediator.component_manager;
	RefVector<AI> ai_components = mgr.get_components_by_type<AI>();

	double dt = LoopTimer::get_instance().get_delta_time();

	for (AI & ai : ai_components) {
		RefVector<Rigidbody> rigidbodies
			= mgr.get_components_by_id<Rigidbody>(ai.game_object_id);
		Rigidbody & rigidbody = rigidbodies.front().get();

		vec2 force = this->calculate(ai);
		vec2 acceleration = force / rigidbody.data.mass;
		rigidbody.data.linear_velocity += acceleration * dt;
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
	const Mediator & mediator = this->mediator;
	ComponentManager & mgr = mediator.component_manager;
	RefVector<Transform> transforms = mgr.get_components_by_id<Transform>(ai.game_object_id);
	Transform & transform = transforms.front().get();
	RefVector<Rigidbody> rigidbodies = mgr.get_components_by_id<Rigidbody>(ai.game_object_id);
	Rigidbody & rigidbody = rigidbodies.front().get();

	vec2 desired_velocity = ai.seek_target - transform.position;
	desired_velocity.normalize();
	desired_velocity *= rigidbody.data.max_linear_velocity;

	return desired_velocity - rigidbody.data.linear_velocity;
}
