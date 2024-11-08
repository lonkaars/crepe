#pragma once

#include "../api/ParticleEmitter.h"

namespace crepe {

class ParticleSystem {
public:
	ParticleSystem();
	void update();

private:
	void emit_particle(ParticleEmitter & emitter,const Transform& transform);
	int calculate_update(int count, double emission);
	void check_bounds(ParticleEmitter & emitter,const Transform& transform);

private:
	//! counter to count updates to determine how many times emit_particle is called.
	uint32_t update_count = 0;
	//! determines the lowest amount of emissionrate (1000 = 0.001 = 1 particle per 1000 updates).
	const uint32_t MAX_UPDATE_COUNT = 100;
};

} // namespace crepe
