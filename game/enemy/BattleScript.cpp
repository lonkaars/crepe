#include "BattleScript.h"
#include "EnemyScript.h"
#include <crepe/api/AI.h>
#include <iostream>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Metadata.h>
using namespace std;
using namespace crepe;

BattleScript::BattleScript() { engine.seed(rd()); }
void BattleScript::init() {
	std::uniform_int_distribution<int> dist(2, 10);
	int random_enemy_amount = dist(this->engine);
	// this->create_battle(random_enemy_amount);
	this->subscribe<BattleStartEvent>([this](const BattleStartEvent & e) -> bool {
		return this->create_battle(e);
	});
}
void BattleScript::fixed_update(duration_t dt) {
	if (!battle_active) return;
	bool enemies_alive = false;
	RefVector<BehaviorScript> enemy_scripts
		= this->get_components_by_tag<BehaviorScript>("enemy");

	for (BehaviorScript & script : enemy_scripts) {
		if (script.active) {
			enemies_alive = true;
		}
	}
	if (!enemies_alive) {
		this->battle_active = false;
		cout << "battle won" << endl;
		this->trigger_event<BattleWonEvent>();
	}
}
bool BattleScript::create_battle(const BattleStartEvent & e) {
	this->battle_active = e.battle;
	this->spawn_enemies(e.num_enemies);
	return false;
}
void BattleScript::spawn_enemies(int amount) {
	RefVector<BehaviorScript> enemy_scripts
		= this->get_components_by_tag<BehaviorScript>("enemy");
	std::uniform_real_distribution<float> dist(70, 150);
	
	for (int i = 0; i < amount; i++) {
		BehaviorScript & script = enemy_scripts[i];
		if(script.active == true) continue;
		script.active = true;
		this->queue_event<SpawnEnemyEvent>(
			SpawnEnemyEvent {
				.speed = dist(engine),
				.column = i,
			},
			script.game_object_id
		);
	}
}
