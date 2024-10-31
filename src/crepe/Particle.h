#pragma once

#include "Position.h"

namespace crepe {

class Particle {
public:
	Position position;
	// FIXME: `Position` is an awkward name for a 2D vector. See FIXME comment in
	// api/Transform.h for fix proposal.
	Position velocity;
	float lifespan;
	bool active;

	Particle();
	void reset(float lifespan, Position position, Position velocity);
	void update(float deltaTime);
	float time_in_life;
};

} // namespace crepe
