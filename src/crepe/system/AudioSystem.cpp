#include "AudioSystem.h"

#include "../manager/ComponentManager.h"
#include "../manager/ResourceManager.h"
#include "../types.h"

using namespace crepe;
using namespace std;

void AudioSystem::fixed_update() {
	ComponentManager & component_manager = this->mediator.component_manager;
	ResourceManager & resource_manager = this->mediator.resource_manager;
	RefVector<AudioSource> components
		= component_manager.get_components_by_type<AudioSource>();

	for (AudioSource & component : components) {
		Sound & resource = resource_manager.get<Sound>(component.source);

		this->diff_update(component, resource);

		this->update_last(component);
	}
}

void AudioSystem::diff_update(AudioSource & component, Sound & resource) {
	SoundContext & context = this->get_context();

	if (component.active != component.last_active) {
		if (!component.active) {
			context.stop(component.voice);
			return;
		}
		if (component.play_on_awake) component.oneshot_play = true;
	}
	if (!component.active) return;

	if (component.oneshot_play) {
		component.voice = context.play(resource);
		context.set_loop(component.voice, component.loop);
		context.set_volume(component.voice, component.volume);
		component.oneshot_play = false;
	}
	if (component.oneshot_stop) {
		context.stop(component.voice);
		component.oneshot_stop = false;
	}
	if (component.volume != component.last_volume) {
		context.set_volume(component.voice, component.volume);
	}
	if (component.loop != component.last_loop) {
		context.set_loop(component.voice, component.loop);
	}
}

void AudioSystem::update_last(AudioSource & component) {
	component.last_active = component.active;
	component.last_loop = component.loop;
	component.last_volume = component.volume;
}

SoundContext & AudioSystem::get_context() {
	if (this->context == nullptr) this->context = make_unique<SoundContext>();
	return *this->context.get();
}
