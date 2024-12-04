#include "../ComponentManager.h"

#include "AISystem.h"

using namespace crepe;

void AISystem::update() {
	ComponentManager & mgr = this->component_manager;
	RefVector<AI> ai_components = mgr.get_components_by_type<AI>();

	for (AI & ai : ai_components) {
		vec2 force = this->calculate(ai);
		//...
	}
}

vec2 AISystem::calculate(AI & ai) {
	vec2 force;

	if (ai.on(AI::BehaviorType::SEEK)) {
		// Seek the target
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
