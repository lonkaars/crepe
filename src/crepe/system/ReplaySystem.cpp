#include "../util/Log.h"
#include "../manager/ReplayManager.h"
#include "../manager/SystemManager.h"

#include "RenderSystem.h"
#include "ReplaySystem.h"

using namespace crepe;
using namespace std;

void ReplaySystem::fixed_update() {
	ReplayManager & replay = this->mediator.replay_manager;

	switch (replay.state) {
		case ReplayManager::IDLE: break;
		case ReplayManager::RECORDING: {
			this->update_recording();
			break;
		}
		case ReplayManager::PLAYING: {
			this->update_playing();
			break;
		}
	}

	this->last_state = replay.state;
}

void ReplaySystem::update_recording() {
	ReplayManager & replay = this->mediator.replay_manager;
	ComponentManager & components = this->mediator.component_manager;

	ReplayManager::Recording & recording = replay.recording;
	recording.frames.push_back(components.save());
	recording.frame++;
}

void ReplaySystem::update_playing() {
	ReplayManager & replay = this->mediator.replay_manager;

	if (this->last_state != ReplayManager::PLAYING) {
		this->playback_begin();
	}

	ReplayManager::Recording & recording = replay.recording;

	if (recording.frames.size() == recording.frame) {
		dbg_log("Finished playback");
		this->playback_end();
		return;
	}

	ComponentManager & components = this->mediator.component_manager;
	ComponentManager::Snapshot & frame = recording.frames.at(recording.frame);

	dbg_logf("Playing recording frame {}", recording.frame);
	components.restore(frame);
	recording.frame++;
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
}

void ReplaySystem::playback_end() {
	SystemManager & systems = this->mediator.system_manager;
	ComponentManager & components = this->mediator.component_manager;

	components.restore(this->playback.components);
	systems.restore(this->playback.systems);

	ReplayManager & replay = this->mediator.replay_manager;
	replay.state = ReplayManager::IDLE;
}

