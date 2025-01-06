#pragma once

#include <crepe/api/Script.h>

class MissileCollisionScript : public crepe::Script {
private:
	bool alive = true;
	bool on_collision(const crepe::CollisionEvent & ev);
public:
	void init();
	void fixed_update(crepe::duration_t dt);
};
