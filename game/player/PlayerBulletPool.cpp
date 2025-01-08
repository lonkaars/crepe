#include "PlayerBulletSubScene.h"
#include "PlayerBulletPool.h"
using namespace std;

void PlayerBulletPool::create_bullets(crepe::Scene & scn) {
	PlayerBulletSubScene bullet;
	while(bullet.create(scn) < this->MAXIMUM_AMOUNT);
}
