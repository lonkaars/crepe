#include "CoinPool.h"
#include "CoinScript.h"
#include "CoinSubScene.h"
#include "api/BehaviorScript.h"
#include "api/GameObject.h"

using namespace crepe;
using namespace std;

void CoinPool::create_coins(crepe::Scene & scn) {
	CoinSubScene coin;
	while(coin.create(scn) < this->MAXIMUM_AMOUNT);
}
