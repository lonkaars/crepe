#include "CoinPool.h"
#include "CoinScript.h"
#include "CoinSubScene.h"
#include "api/BehaviorScript.h"
#include "api/GameObject.h"

using namespace crepe;
using namespace std;

void CoinPool::create_coins(crepe::Scene & scn) {
	int amount = 0;
	CoinSubScene coin;
	while(amount < this->MAXIMUM_AMOUNT){
		amount = coin.create(scn,amount);
	}
}
