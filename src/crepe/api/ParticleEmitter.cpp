#include "ParticleEmitter.h"

using namespace crepe;

ParticleEmitter::ParticleEmitter(game_object_id_t game_object_id, const Data & data)
	: Component(game_object_id),
	  data(data) {
	for (size_t i = 0; i < this->data.max_particles; i++) {
		this->data.particles.emplace_back();
	}
}
