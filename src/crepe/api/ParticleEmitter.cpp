#include "ParticleEmitter.h"
#include "api/Sprite.h"

using namespace crepe;
using namespace std;

ParticleEmitter::ParticleEmitter(game_object_id_t game_object_id, const Sprite & sprite,
								 const Data & data)
	: Component(game_object_id),
	  sprite(sprite),
	  data(data) {
	for (size_t i = 0; i < this->data.max_particles; i++) {
		this->particles.emplace_back();
	}
}

unique_ptr<Component> ParticleEmitter::save() const {
	return unique_ptr<Component>{new ParticleEmitter(*this)};
}

void ParticleEmitter::restore(const Component & snapshot) {
	*this = static_cast<const ParticleEmitter &>(snapshot);
}

ParticleEmitter & ParticleEmitter::operator=(const ParticleEmitter & other) {
	this->particles = other.particles;
	return *this;
}
