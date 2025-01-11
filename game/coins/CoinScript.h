#pragma once

#include "api/Script.h"

class CoinScript : public crepe::Script {
public:
	void init() override;
	void fixed_update(crepe::duration_t dt) override;
	bool on_collision(const crepe::CollisionEvent & collisionData);
	bool save();

private:
	int amount = 0;
};
