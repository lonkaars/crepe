#include "EnemyBulletSubScene.h"
#include "EnemyBulletPool.h"
using namespace std;

void EnemyBulletPool::create_bullets(crepe::Scene & scn) {
	EnemyBulletSubScene bullet;
	while(bullet.create(scn) < this->MAXIMUM_AMOUNT);
}
