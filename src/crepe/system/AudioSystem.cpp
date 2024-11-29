#include "AudioSystem.h"

#include "../manager/ComponentManager.h"
#include "../manager/ResourceManager.h"
#include "../types.h"

using namespace crepe;
using namespace std;

void AudioSystem::update() {
	ComponentManager & component_manager = this->mediator.component_manager;
	ResourceManager & resource_manager = this->mediator.resource_manager;
	RefVector<AudioSource> components = component_manager.get_components_by_type<AudioSource>();

	for (AudioSource & component : components) {
		if (!component.active) continue;

		Sound & sound = resource_manager.get<Sound>(component.source);
		if (component.private_data.empty())
			component.private_data.set<ComponentPrivate>();
		auto & data = component.private_data.get<ComponentPrivate>();
		// TODO: lots of state diffing


		this->update_private(component, data);
	}
}

void AudioSystem::update_private(const AudioSource & component, ComponentPrivate & data) {
	data.last_active = component.active;
	data.last_loop = component.loop;
	data.last_playing = component.playing;
	data.last_volume = component.volume;
}

