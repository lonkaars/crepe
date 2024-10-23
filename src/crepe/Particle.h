#pragma once

#include "Position.h"

namespace crepe {

class Particle {
public:
	Position position;
	Position velocity;
	float lifespan;
	bool active;

	Particle();
	void reset(float lifespan, Position position, Position velocity);
	void update(float deltaTime);
	float time_in_life;
};

} // namespace crepe
