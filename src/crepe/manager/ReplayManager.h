#pragma once

#include <unordered_map>

#include "Manager.h"
#include "ComponentManager.h"
#include "util/OptionalRef.h"

namespace crepe {

class ReplaySystem;

typedef size_t recording_t;

/**
 * \brief Replay manager
 *
 */
class ReplayManager : public Manager {
	// TODO: Delete recordings at end of scene
public:
	ReplayManager(Mediator & mediator);

public:
	void record_start();
	recording_t record_end();
	void play(recording_t handle);
	void release(recording_t handle);
	
public:
	enum State {
		IDLE,
		RECORDING,
		PLAYING,
	};
	State get_state() const;

public:
	void frame_record();
	bool frame_step();

private:
	struct Recording {
		size_t frame = 0;
		std::vector<ComponentManager::Snapshot> frames;
	};
	State state = IDLE;
	OptionalRef<Recording> recording;
	recording_t id = -1;
	std::unordered_map<recording_t, std::unique_ptr<Recording>> memory;
};

} // namespace crepe
