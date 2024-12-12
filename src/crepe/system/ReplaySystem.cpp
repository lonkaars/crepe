#include "../manager/ReplayManager.h"
#include "../manager/SystemManager.h"

#include "EventSystem.h"
#include "RenderSystem.h"
#include "ReplaySystem.h"

using namespace crepe;
using namespace std;

void ReplaySystem::fixed_update() {
	ReplayManager & replay = this->mediator.replay_manager;
	ReplayManager::State state = replay.get_state();
	ReplayManager::State last_state = this->last_state;
	this->last_state = state;

	switch (state) {
		case ReplayManager::IDLE:
			break;
		case ReplayManager::RECORDING: {
			replay.frame_record();
			break;
		}
		case ReplayManager::PLAYING: {
			if (last_state != ReplayManager::PLAYING) this->playback_begin();
			bool last = replay.frame_step();
			if (last) this->playback_end();
			break;
		}
	}
}

void ReplaySystem::playback_begin() {
	SystemManager & systems = this->mediator.system_manager;
	ComponentManager & components = this->mediator.component_manager;

	this->playback = {
		.components = components.save(),
		.systems = systems.save(),
	};

	systems.disable_all();
	systems.get_system<RenderSystem>().active = true;
	systems.get_system<ReplaySystem>().active = true;
	systems.get_system<EventSystem>().active = true;
}

void ReplaySystem::playback_end() {
	SystemManager & systems = this->mediator.system_manager;
	ComponentManager & components = this->mediator.component_manager;

	components.restore(this->playback.components);
	systems.restore(this->playback.systems);
}
