#pragma once

#include "../manager/ReplayManager.h"

#include "System.h"

namespace crepe {

class ReplaySystem : public System {
public:
	using System::System;

	void fixed_update() override;

private:
	ReplayManager::State last_state = ReplayManager::IDLE;
	void update_recording();
	void update_playing();

	std::unordered_map<std::type_index, bool> system_active_snapshot;
	void playback_begin();
	void playback_end();
};

}

