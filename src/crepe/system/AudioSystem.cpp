#include "AudioSystem.h"

#include "../api/AudioSource.h"
#include "../manager/ComponentManager.h"
#include "../manager/ResourceManager.h"
#include "../types.h"

using namespace crepe;
using namespace std;

void AudioSystem::update() {
	ComponentManager & component_manager = this->mediator.component_manager;
	ResourceManager & resource_manager = this->mediator.resource_manager;
	RefVector<AudioSource> components = component_manager.get_components_by_type<AudioSource>();

	for (auto component_ref : components) {
		AudioSource & component = component_ref.get();
		if (!component.active) continue;

		Sound & sound = resource_manager.get<Sound>(component.source);
		// TODO: lots of state diffing
	}
}

