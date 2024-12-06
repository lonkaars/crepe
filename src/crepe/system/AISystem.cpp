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
		/*vec2 force_to_add = this->path_follow(ai);

		if (!this->accumulate_force(ai, force, force_to_add)) {
			return force;
		}*/
	}

	return force;
}

bool AISystem::accumulate_force(AI & ai, vec2 & running_total, vec2 force_to_add) {
	float magnitude = running_total.length();
	float magnitude_remaining = ai.max_force - magnitude;

	if (magnitude_remaining <= 0.0f) {
		return false;
	}

	float magnitude_to_add = force_to_add.length();
	if (magnitude_to_add < magnitude_remaining) {
		running_total += force_to_add;
	} else {
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
