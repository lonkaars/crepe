#pragma once

#include "../manager/ReplayManager.h"
#include "../manager/SystemManager.h"

#include "System.h"

namespace crepe {

/**
 * \brief ReplayManager helper system
 *
 * This system records and replays recordings using ReplayManager.
 */
class ReplaySystem : public System {
public:
	using System::System;

	void fixed_update() override;

private:
	//! Last ReplayManager state
	ReplayManager::State last_state = ReplayManager::IDLE;

	/**
	 * \brief Playback snapshot
	 *
	 * When starting playback, the component state is saved and most systems are disabled. This
	 * struct stores the engine state before ReplayManager::play is called.
	 */
	struct Snapshot {
		ComponentManager::Snapshot components;
		SystemManager::Snapshot systems;
	};
	//! Before playback snapshot
	Snapshot playback;

	//! Snapshot state and disable systems during playback
	void playback_begin();
	//! Restore state from before \c playback_begin()
	void playback_end();
};

} // namespace crepe
