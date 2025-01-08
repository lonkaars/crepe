#pragma once

#include <crepe/api/Event.h>
#include <crepe/api/Script.h>

class CollisionScript : public crepe::Script {
public:
	void init();

private:
	bool on_collision(const crepe::CollisionEvent & ev);
};
