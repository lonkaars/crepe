#include "MissilePool.h"
#include "MissileSubScene.h"

#include <crepe/api/Scene.h>

using namespace std;
using namespace crepe;

MissilePool::MissilePool(Scene & scn) {
	int amount = 0;
	MissileSubScene missile;
	while (amount < this->MAX_MISSILE_COUNT) {
		missile.create(scn);
		amount++;
	}
}
