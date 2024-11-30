#include "AudioSystem.h"

#include "../manager/ComponentManager.h"
#include "../manager/ResourceManager.h"
#include "../types.h"

using namespace crepe;
using namespace std;

void AudioSystem::update() {
	ComponentManager & component_manager = this->mediator.component_manager;
	ResourceManager & resource_manager = this->mediator.resource_manager;
	RefVector<AudioSource> components
		= component_manager.get_components_by_type<AudioSource>();

	for (AudioSource & component : components) {
		Sound & resource = resource_manager.get<Sound>(component.source);

		if (component.private_data.empty()) {
			auto & data = component.private_data.set<ComponentPrivate>();
			this->update_last(component, data);
			data.last_active = false;
		}
		auto & data = component.private_data.get<ComponentPrivate>();

		this->diff_update(component, data, resource);

		this->update_last(component, data);
	}
}

void AudioSystem::diff_update(AudioSource & component, ComponentPrivate & data,
							  Sound & resource) {
	SoundContext & context = this->get_context();

	if (component.active != data.last_active) {
		if (component.active) {
			component.oneshot_play = component.play_on_awake;
		} else {
			context.stop(data.handle);
			return;
		}
	}
	if (!component.active) return;

	if (component.oneshot_play) {
		data.handle = context.play(resource);
		component.oneshot_play = false;
	}
	if (component.oneshot_stop) {
		context.stop(data.handle);
		component.oneshot_stop = false;
	}
	if (component.volume != data.last_volume) {
		context.set_volume(resource, data.handle, component.volume);
	}
	if (component.loop != data.last_loop) {
		context.set_loop(resource, data.handle, component.loop);
	}
}

void AudioSystem::update_last(const AudioSource & component, ComponentPrivate & data) {
	data.last_active = component.active;
	data.last_loop = component.loop;
	data.last_volume = component.volume;
}

SoundContext & AudioSystem::get_context() {
	if (this->context.empty()) this->context.set<SoundContext>();
	return this->context.get<SoundContext>();
}
