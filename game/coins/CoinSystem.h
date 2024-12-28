#pragma once

#include "api/Scene.h"


class CoinSystem {
public:
	void create_coins(crepe::Scene & scn);
private:
	static constexpr int MAXIMUM_AMOUNT = 100;
};

