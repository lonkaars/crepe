#pragma once

#include "Manager.h"

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
	bool recording;
	struct Recording {
		recording_t id;
		std::vector<Memento> frames;
	};
public:
	void record_start();
	recording_t record_end();
	
};

} // namespace crepe
