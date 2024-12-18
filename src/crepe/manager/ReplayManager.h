#pragma once

#include <unordered_map>

#include "../util/OptionalRef.h"

#include "ComponentManager.h"
#include "Manager.h"

namespace crepe {

//! Handle to recording held by ReplayManager
typedef size_t recording_t;

/**
 * \brief Replay manager
 *
 * The replay manager is responsible for creating, storing and restoring ComponentManager
 * snapshots. Sequential snapshots can be recorded and replayed in combination with
 * ReplaySystem.
 */
class ReplayManager : public Manager {
	// TODO: Delete recordings at end of scene

public:
	ReplayManager(Mediator & mediator);

public:
	//! Start a new recording
	void record_start();
	/**
	 * \brief End the latest recording started by \c record_start()
	 * \returns Handle to recording
	 */
	recording_t record_end();
	/**
	 * \brief Play a recording
	 * \param handle Handle to recording (as returned by \c record_end())
	 */
	void play(recording_t handle);
	/**
	 * \brief Delete a recording from memory
	 * \param handle Handle to recording (as returned by \c record_end())
	 */
	void release(recording_t handle);

public:
	//! Internal state
	enum State {
		IDLE, //!< Not doing anything
		RECORDING, //!< Currently recording
		PLAYING, //!< Currently playing back a recording
	};
	//! Get current internal state
	State get_state() const;

public:
	/**
	 * \brief Record a single frame to the current recording
	 *
	 * This function is called by ReplaySystem after the game programmer has called \c
	 * record_start()
	 */
	void frame_record();
	/**
	 * \brief Play the next frame of the current recording
	 *
	 * \returns `true` if the recording is finished playing
	 * \returns `false` if there are more frames
	 *
	 * This function also automatically resets the internal state from PLAYING to IDLE at the end
	 * of a recording.
	 */
	bool frame_step();

private:
	/**
	 * \brief Recording data
	 */
	struct Recording {
		//! Current frame being shown
		size_t frame = 0;
		//! All frames in recording
		std::vector<ComponentManager::Snapshot> frames;
	};
	//! Internal state
	State state = IDLE;
	//! Current recording handle
	recording_t id = -1;
	//! Current recording data
	OptionalRef<Recording> recording;
	//! Recording storage
	std::unordered_map<recording_t, std::unique_ptr<Recording>> memory;
};

} // namespace crepe
