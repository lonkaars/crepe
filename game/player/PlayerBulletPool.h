#pragma once

#include <crepe/api/Scene.h>

class PlayerBulletPool {
public:
	void create_bullets(crepe::Scene & scn);
private:
	static constexpr int MAXIMUM_AMOUNT = 20;
};
