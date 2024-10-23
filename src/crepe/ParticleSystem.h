#pragma once

#include "api/ParticleEmitter.h"

namespace crepe {

class ParticleSystem {
public:
	ParticleSystem();
	void update();

private:
	void emit_particle(ParticleEmitter & emitter); //emits a new particle

	float elapsed_time; //elapsed time since the last emission
};

} // namespace crepe
