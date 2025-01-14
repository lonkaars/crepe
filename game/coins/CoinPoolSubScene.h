#pragma once

#include <crepe/api/Scene.h>

class CoinPoolSubScene {
public:
	void create_coins(crepe::Scene & scn);

private:
	static constexpr int MAXIMUM_AMOUNT = 100;
};
