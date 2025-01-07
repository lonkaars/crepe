#pragma once

#include <crepe/api/Scene.h>

class MissilePool {
public:
	MissilePool(crepe::Scene & scn);
private:
	static constexpr unsigned int MAX_MISSILE_COUNT = 5;

};
