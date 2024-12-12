#include <format>

#include "ReplayManager.h"
#include "Manager.h"

using namespace crepe;
using namespace std;

ReplayManager::ReplayManager(Mediator & mediator) : Manager(mediator) {
	mediator.replay_manager = *this;
}

void ReplayManager::record_start() {
	if (this->state == RECORDING) this->release(this->id);
	this->id++;
	this->memory[this->id] = make_unique<Recording>();
	this->recording = *this->memory.at(this->id);
	this->state = RECORDING;
}

recording_t ReplayManager::record_end() {
	this->state = IDLE;
	return this->id;
}

void ReplayManager::play(recording_t handle) {
	if (!this->memory.contains(handle))
		throw out_of_range(format("ReplayManager: no recording for handle {}", handle));
	this->recording = *this->memory.at(handle);
	this->recording->frame = 0;
	this->state = PLAYING;
}

void ReplayManager::release(recording_t handle) {
	if (!this->memory.contains(handle))
		return;
	this->memory.erase(handle);
}

void ReplayManager::frame_record() {
	ComponentManager & components = this->mediator.component_manager;
	Recording & recording = this->recording;

	recording.frames.push_back(components.save());
	recording.frame++;
}

bool ReplayManager::frame_step() {
	ComponentManager & components = this->mediator.component_manager;
	Recording & recording = this->recording;

	ComponentManager::Snapshot & frame = recording.frames.at(recording.frame);

	components.restore(frame);
	recording.frame++;

	if (recording.frame < recording.frames.size()) return false;
	// end of recording
	recording.frame = 0;
	this->state = IDLE;
	return true;
}

ReplayManager::State ReplayManager::get_state() const {
	return this->state;
}

