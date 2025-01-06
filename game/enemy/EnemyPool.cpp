#include "EnemySubScene.h"
#include "EnemyPool.h"
using namespace std;
void EnemyPool::create_enemies(crepe::Scene & scn) {
	EnemySubScene enemy;
	while(enemy.create(scn) < this->MAXIMUM_AMOUNT);
}
