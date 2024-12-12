#include "ParticleEmitter.h"

using namespace crepe;
using namespace std;

ParticleEmitter::ParticleEmitter(game_object_id_t game_object_id, const Data & data)
	: Component(game_object_id),
	  data(data) {
	for (size_t i = 0; i < this->data.max_particles; i++) {
		this->data.particles.emplace_back();
	}
}

unique_ptr<Component> ParticleEmitter::save() const {
	return unique_ptr<Component>{new ParticleEmitter(*this)};
}

void ParticleEmitter::restore(const Component & snapshot) {
	*this = static_cast<const ParticleEmitter &>(snapshot);
}

ParticleEmitter & ParticleEmitter::operator=(const ParticleEmitter & other) {
	data.particles = other.data.particles;
	return *this;
}

