#include "MissilePool.h"
#include "MissileSubScene.h"

#include <crepe/api/Scene.h>

using namespace std;
using namespace crepe;

MissilePool::MissilePool(Scene & scn) {
	MissileSubScene missile;
	while (missile.create(scn) < this->MAX_MISSILE_COUNT) {
	}
}
