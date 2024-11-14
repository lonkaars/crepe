#include "AudioSystem.h"
#include "ComponentManager.h"

#include "../api/AudioSource.h"

using namespace crepe;
using namespace std;

AudioSystem::AudioSystem(SoundContext & ctx) : ctx(ctx) {}

void AudioSystem::update() {
	vector<reference_wrapper<AudioSource>> components = this->compmgr.get_components_by_type<AudioSource>();

	for (auto component_ref : components) {
		AudioSource & component = component_ref.get();
		if (!component.active) continue;

		// TODO: fetch Sound instance from resourcemanager
		// TODO: lots of state diffing
	}
}

