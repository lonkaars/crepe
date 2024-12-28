#include "CoinPool.h"
#include "CoinSubScene.h"

using namespace crepe;
using namespace std;

void CoinPool::create_coins(crepe::Scene & scn) {
	CoinSubScene coin;
	while(coin.create(scn) < this->MAXIMUM_AMOUNT);
}
