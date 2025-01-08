#pragma once

#include <crepe/api/Scene.h>

class EnemyPool {
public:
	void create_enemies(crepe::Scene & scn);
private:
	static constexpr int MAXIMUM_AMOUNT = 10;
};
