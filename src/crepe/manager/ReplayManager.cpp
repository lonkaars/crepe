#include "../util/Log.h"

#include "ReplayManager.h"
#include "Manager.h"

using namespace crepe;
using namespace std;

ReplayManager::ReplayManager(Mediator & mediator) : Manager(mediator) {
	mediator.replay_manager = *this;
}

void ReplayManager::record_start() {
	if (this->recording) this->release(this->current_recording);
	this->current_recording++;
	this->recording = true;
}

recording_t ReplayManager::record_end() {
	this->recording = false;
	return this->current_recording;
}

void ReplayManager::play(recording_t handle) {
	if (!this->memory.contains(handle))
		throw out_of_range(format("ReplayManager: no recording for handle {}", handle));
	Recording & recording = *this->memory.at(handle);

	dbg_log("TODO: magic");
}

void ReplayManager::release(recording_t handle) {
	dbg_log("release");

}

