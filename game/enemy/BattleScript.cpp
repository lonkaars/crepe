#include <iostream>
#include "BattleScript.h"
#include <crepe/api/AI.h>
#include "EnemyScript.h"
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Metadata.h>
#include "BattleWonEvent.h"
#include "EnemyScript.h"
using namespace std;
using namespace crepe;
// stop player movement
// spawn enemies
// resume game once enemies are defeated
// optional: spawn lazers during fight
BattleScript::BattleScript(){
	engine.seed(rd());
}
void BattleScript::init(){
	std::uniform_int_distribution<int> dist(2,10);
	int random_enemy_amount = dist(this->engine);
	// this->create_battle(random_enemy_amount);
	this->subscribe<BattleStartEvent>([this](const BattleStartEvent& e) -> bool {
		return this->create_battle(e);
	});
}
void BattleScript::fixed_update(duration_t dt){
	bool enemies_alive = false;
	RefVector<BehaviorScript> enemy_scripts = this->get_components_by_tag<BehaviorScript>("enemy");
	
	for(BehaviorScript& script : enemy_scripts){
		if(script.active){
			enemies_alive = true;
		}
	}
	if(!enemies_alive){
		this->trigger_event<BattleWonEvent>();
	}
}
bool BattleScript::create_battle(const BattleStartEvent& e){
	RefVector<BehaviorScript> enemy_scripts = this->get_components_by_tag<BehaviorScript>("enemy");
	std::uniform_real_distribution<float> dist(10,30);
	for(int i = 0; i < e.num_enemies;i++){
		BehaviorScript& script = enemy_scripts[i];
		script.active = true;
		this->trigger_event<SpawnEnemyEvent>(SpawnEnemyEvent{
			.speed = dist(engine),
			.column = i,
		},script.game_object_id);
		
	}
	return true;
}

