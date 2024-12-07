#include "ParticleEmitter.h"
#include "api/Sprite.h"

using namespace crepe;

ParticleEmitter::ParticleEmitter(game_object_id_t game_object_id, const Sprite & sprite, const Data & data)
	: Component(game_object_id),
	  sprite(sprite), data(data) {
	for (size_t i = 0; i < this->data.max_particles; i++) {
		this->data.particles.emplace_back();
	}
}
