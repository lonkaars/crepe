#pragma once

#include "../manager/ReplayManager.h"
#include "../manager/SystemManager.h"

#include "System.h"

namespace crepe {

class ReplaySystem : public System {
public:
	using System::System;

	void fixed_update() override;

private:
	ReplayManager::State last_state = ReplayManager::IDLE;

	struct Snapshot {
		ComponentManager::Snapshot components;
		SystemManager::Snapshot systems;
	};
	Snapshot playback;

	void playback_begin();
	void playback_end();
};

}

