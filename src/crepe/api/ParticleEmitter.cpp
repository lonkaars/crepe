#include "ParticleEmitter.h"
#include "Particle.h"

using namespace crepe;

ParticleEmitter::ParticleEmitter(uint32_t game_object_id, const Data & data)
	: Component(game_object_id), data(data) {
	for (size_t i = 0; i < this->data.max_particles; i++) {
		this->data.particles.emplace_back();
	}
}

ParticleEmitter::~ParticleEmitter() {
	std::vector<Particle>::iterator it = this->data.particles.begin();
	while (it != this->data.particles.end()) {
		it = this->data.particles.erase(it);
	}
}
