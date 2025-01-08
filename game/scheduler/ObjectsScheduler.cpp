

#include "ObjectsScheduler.h"

#include "../missile/SpawnEvent.h"

#include "api/Transform.h"
#include <iostream>

using namespace crepe;

void ObjectsScheduler::init() {

	for (int i = 0; i < 3; i++) {
		this->obstacles.push_back([this]() {
			trigger_event<MissileSpawnEvent>(MissileSpawnEvent {});
		});
	}
}

void ObjectsScheduler::fixed_update(duration_t dt) {
	auto pos_x = this->get_components_by_name<Transform>("camera").front().get().position.x;

	int current_check = (pos_x  - 500) / 300;
	if (current_check > this->last_check) {
		std::cout << "TRIGGER " << current_check << " " << last_check << std::endl;
			trigger_event<MissileSpawnEvent>(MissileSpawnEvent {});
		//this->obstacles[0]();
		this->last_check = current_check;
	}
}
