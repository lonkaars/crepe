#pragma once

#include "api/Transform.h"

namespace crepe {

class Particle {
public:
	Vector2 position;
	Vector2 velocity;
	Vector2 force_over_time;
	uint32_t lifespan;
	bool active = false;
	uint32_t time_in_life = 0;
	double angle;

	Particle() = default;
	void reset(uint32_t lifespan, Vector2 position, Vector2 velocity,double angle);
	void update();
	void stop_movement();
	
};

} // namespace crepe
