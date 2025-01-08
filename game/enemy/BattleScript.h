#pragma once

#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Event.h>
#include <crepe/api/Script.h>
#include <random>
struct BattleWonEvent : public crepe::Event {};

struct BattleStartEvent : public crepe::Event {
public:
	int num_enemies = 0;
};
class BattleScript : public crepe::Script {
public:
	BattleScript();
	void init() override;
	void fixed_update(crepe::duration_t dt) override;

private:
	bool battle_active = false;
	std::random_device rd;
	std::default_random_engine engine;
	bool create_battle(const BattleStartEvent & e);
};
