#pragma once

#include <unordered_map>

#include "Manager.h"
#include "ComponentManager.h"
#include "util/OptionalRef.h"

namespace crepe {

class ReplaySystem;

typedef size_t recording_t;

class ReplayManager : public Manager {
public:
	ReplayManager(Mediator & mediator);
	friend class ReplaySystem;

protected:
	void record_frame();

private:
	struct Recording {
		size_t frame = 0;
		std::vector<ComponentManager::Snapshot> frames;
	};

	enum State {
		IDLE,
		RECORDING,
		PLAYING,
	};

	State state = IDLE;
	OptionalRef<Recording> recording;
	recording_t id = -1;

	std::unordered_map<recording_t, std::unique_ptr<Recording>> memory;
public:
	void record_start();
	recording_t record_end();
	void play(recording_t handle);
	void release(recording_t handle);
};

} // namespace crepe
