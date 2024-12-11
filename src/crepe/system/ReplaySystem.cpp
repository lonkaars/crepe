#include "system/ScriptSystem.h"

#include "../manager/ReplayManager.h"

#include "ReplaySystem.h"

#include "../api/LoopManager.h"

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
		this->playback_end();
		return;
	}

	ComponentManager & components = this->mediator.component_manager;
	ComponentManager::Snapshot & frame = recording.frames.at(recording.frame);

	components.restore(frame);
	recording.frame++;
}

void ReplaySystem::playback_begin() {
	LoopManager & loop_manager = this->mediator.loop_manager;
	// TODO: store system active state
	// TODO: disable most systems
	// TODO: store components snapshot
}

void ReplaySystem::playback_end() {
	ReplayManager & replay = this->mediator.replay_manager;

	replay.state = ReplayManager::IDLE;

	LoopManager & loop_manager = this->mediator.loop_manager;

	// TODO: restore system active state snapshot
	// TODO: restore components snapshot
}

