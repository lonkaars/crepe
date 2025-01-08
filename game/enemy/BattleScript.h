#pragma once

#include <crepe/api/Script.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Event.h>
#include <random>
struct BattleStartEvent : public crepe::Event{
	public: 
	int num_enemies = 0;
};
class BattleScript : public crepe::Script{
	public:
	BattleScript();
	void init() override;
	void fixed_update(crepe::duration_t dt) override;
	private:
	std::random_device rd;
	std::default_random_engine engine;
	bool create_battle(const BattleStartEvent& e);
};
