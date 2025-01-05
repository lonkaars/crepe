#pragma once

#include "api/Script.h"

class CoinScript : public crepe::Script {
public:
	void init() override;
	bool on_collision(const crepe::CollisionEvent & collisionData);
};
