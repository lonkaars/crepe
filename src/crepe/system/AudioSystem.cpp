#include "AudioSystem.h"
#include "ComponentManager.h"

#include "../api/AudioSource.h"

using namespace crepe;
using namespace std;

void AudioSystem::update() {
	ComponentManager & mgr = this->component_manager;
	vector<reference_wrapper<AudioSource>> components = mgr.get_components_by_type<AudioSource>();

	for (auto component_ref : components) {
		AudioSource & component = component_ref.get();
		if (!component.active) continue;

		// TODO: fetch Sound instance from resourcemanager
		// TODO: lots of state diffing
	}
}

