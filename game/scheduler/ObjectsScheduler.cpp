

#include "ObjectsScheduler.h"

#include "../Random.h"
#include "../missile/SpawnEvent.h"
#include "api/Transform.h"
#include "prefab/ZapperPoolSubScene.h"
#include <iostream>

using namespace crepe;
void ObjectsScheduler::preset_0() { trigger_event<MissileSpawnEvent>(MissileSpawnEvent {}); }
void ObjectsScheduler::preset_1() { trigger_event<MissileSpawnEvent>(MissileSpawnEvent {}); }
void ObjectsScheduler::preset_2() { trigger_event<CreateZapperEvent>(CreateZapperEvent {}); }
void ObjectsScheduler::preset_3() {}
void ObjectsScheduler::preset_4() {}
void ObjectsScheduler::boss_fight_1() { std::cout << "Boss fight" << std::endl; }

void ObjectsScheduler::init() {
	this->obstacles.push_back([this]() { preset_0(); });
	this->obstacles.push_back([this]() { preset_1(); });
	this->obstacles.push_back([this]() { preset_2(); });

	this->obstacles.push_back([this]() { boss_fight_1(); });

	// subscribe to battlewonevent
}

void ObjectsScheduler::fixed_update(duration_t dt) {
	int pos_x
		= (int) this->get_components_by_name<Transform>("camera").front().get().position.x;

	int boss_check = (pos_x - this->start_offset) / this->boss_fight_interval;
	if (boss_check > this->last_boss_check) {
		this->obstacles[2]();
		this->last_boss_check = boss_check;
	}
	int obstacle_check = (pos_x - this->start_offset) / this->obstacle_interval;
	if (obstacle_check > this->last_obstacle_check) {
		this->obstacles[Random::i(this->obstacles.size() - 1, 0)]();
		this->last_obstacle_check = obstacle_check;
	}
}
