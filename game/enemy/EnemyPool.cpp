#include "EnemyPool.h"
#include "EnemySubScene.h"
using namespace std;
void EnemyPool::create_enemies(crepe::Scene & scn) {
	EnemySubScene enemy;
	int amount = 0;
	while (amount < ENEMY_POOL_MAX) {
		amount = enemy.create(scn, amount);
	}
}
