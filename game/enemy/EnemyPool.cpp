#include "EnemyPool.h"
#include "EnemySubScene.h"
using namespace std;
void EnemyPool::create_enemies(crepe::Scene & scn) {
	EnemySubScene enemy;
	int amount = 0;
	while (amount < this->MAXIMUM_AMOUNT) {
		amount = enemy.create(scn, amount);
	}
}
