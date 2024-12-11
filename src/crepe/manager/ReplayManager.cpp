#include "ReplayManager.h"
#include "manager/Manager.h"

using namespace crepe;

ReplayManager::ReplayManager(Mediator & mediator) : Manager(mediator) {
	mediator.replay_manager = *this;
}

void ReplayManager::record_start() {

}

recording_t ReplayManager::record_end() {
	return 0;
}

void ReplayManager::play(recording_t handle) {

}

void ReplayManager::release(recording_t handle) {

}

