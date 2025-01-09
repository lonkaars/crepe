#include "BattleScript.h"
#include "EnemyScript.h"
#include "../enemy/EnemyConfig.h"
#include "api/Transform.h"
#include <crepe/api/AI.h>
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
	RefVector<AI> enemy_ai
		= this->get_components_by_tag<AI>("enemy");

	for (AI & ai : enemy_ai) {
		if (ai.active) {
			enemies_alive = true;
		}
	}
	if (!enemies_alive) {
		this->battle_active = false;
		this->trigger_event<BattleWonEvent>();
	}
}
bool BattleScript::create_battle(const BattleStartEvent & e) {
	this->battle_active = e.battle;
	this->spawn_enemies(e.num_enemies);
	return false;
}
void BattleScript::spawn_enemies(int amount) {
	RefVector<AI> enemy_ai
		= this->get_components_by_tag<AI>("enemy");
	std::uniform_real_distribution<float> dist(70, 150);
	int spawned = 0;
	for (int i = 0; i < 7; i++) {
		AI& ai = enemy_ai[i];
		Transform& enemy_transform = this->get_components_by_id<Transform>(ai.game_object_id).front();
		if (ai.active == true || enemy_transform.position != ENEMY_POOL_LOCATION) continue;
		this->queue_event<SpawnEnemyEvent>(
			SpawnEnemyEvent {
				.speed = dist(engine),
				.column = i,
			},
			ai.game_object_id
		);
		spawned++;
		if(spawned >= amount){
			return;
		}
	}
}
