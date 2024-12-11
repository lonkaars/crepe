#pragma once

#include "Manager.h"
#include "ComponentManager.h"
#include <unordered_map>

namespace crepe {

class ReplaySystem;
class Memento;

typedef size_t recording_t;

class ReplayManager : public Manager {
public:
	ReplayManager(Mediator & mediator);
	friend class ReplaySystem;

protected:
	void record_frame();

private:
	typedef std::vector<ComponentManager::Snapshot> Recording;

	bool recording = false;
	recording_t current_recording = -1;


	std::unordered_map<recording_t, std::unique_ptr<Recording>> memory;
public:
	void record_start();
	recording_t record_end();
	void play(recording_t handle);
	void release(recording_t handle);
};

} // namespace crepe
