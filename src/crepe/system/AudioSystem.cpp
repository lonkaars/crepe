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

		Sound & resource = resource_manager.get<Sound>(component.source);

		if (component.private_data.empty()) {
			auto & data = component.private_data.set<ComponentPrivate>();
			this->update_last(component, data);
		}
		auto & data = component.private_data.get<ComponentPrivate>();

		this->diff_update(component, data, resource);

		this->update_last(component, data);
	}
}

void AudioSystem::diff_update(AudioSource & component, const ComponentPrivate & data, Sound & resource) {
	bool update_playing = component.playing != data.last_playing;
	bool update_volume = component.volume != data.last_volume;
	bool update_loop = component.loop != data.last_loop;
	bool update_active = component.active != data.last_active;

	if (update_active)
	if (component.rewind) {
		component.playing = false;
		// this->context.rewind(resource, data.handle);
	}

}

void AudioSystem::update_last(const AudioSource & component, ComponentPrivate & data) {
	data.last_active = component.active;
	data.last_loop = component.loop;
	data.last_playing = component.playing;
	data.last_volume = component.volume;
}

