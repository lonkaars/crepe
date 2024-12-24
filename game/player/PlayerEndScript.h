#pragma once

#include <crepe/api/Script.h>

class PlayerEndScript : public crepe::Script {
public:
	void init();

private:
	bool on_collision(const crepe::CollisionEvent & ev);

private:
	int jump = 0;
};
