#include "EnemyBulletSubScene.h"
#include "EnemyBulletPool.h"
using namespace std;

void EnemyBulletPool::create_bullets(crepe::Scene & scn) {
	EnemyBulletSubScene bullet;
	int amount = 0;
	while (amount < this->MAXIMUM_AMOUNT) {
		amount = bullet.create(scn, amount);
	}
}
