#include "PlayerBulletPool.h"
#include "PlayerBulletSubScene.h"
using namespace std;

void PlayerBulletPool::create_bullets(crepe::Scene & scn) {
	PlayerBulletSubScene bullet;
	int amount = 0;
	while (amount < this->MAXIMUM_AMOUNT) {
		amount = bullet.create(scn, amount);
	}
}
