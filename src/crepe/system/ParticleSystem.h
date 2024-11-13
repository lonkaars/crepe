#pragma once

#include "../api/ParticleEmitter.h"

#include "System.h"

namespace crepe {

class ParticleSystem : public System {
public:
	using System::System;
	void update() override;

private:
	//! Emits a new particle
	void emit_particle(ParticleEmitter & emitter);

	//! Elapsed time since the last emission
	float elapsed_time = 0.0;
	// TODO: to std::chrono::duration
};

} // namespace crepe
