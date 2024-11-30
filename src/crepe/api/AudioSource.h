#pragma once

#include "../Component.h"
#include "../types.h"
#include "../util/Private.h"

#include "Asset.h"
#include "GameObject.h"

namespace crepe {

class AudioSystem;

//! Audio source component
class AudioSource : public Component {
	//! AudioSource components are handled by AudioSystem
	friend class AudioSystem;

protected:
	AudioSource(game_object_id_t id, const Asset & source);
	//! Only ComponentManager can create components
	friend class ComponentManager;

public:
	// But std::unique_ptr needs to be able to destoy this component again
	virtual ~AudioSource() = default;

public:
	//! Start or resume this audio source
	void play(bool looping = false);
	//! Stop this audio source
	void stop();

public:
	//! Play when this component becomes active
	bool play_on_awake = false;
	//! Repeat the current audio clip during playback
	bool loop = false;
	//! Normalized volume (0.0 - 1.0)
	float volume = 1.0;

private:
	//! This audio source's clip
	const Asset source;

	/**
	 * \name One-shot state variables
	 *
	 * These variables trigger function calls when set to true, and are unconditionally reset on
	 * every system update.
	 *
	 * \{
	 */
	//! Play this sample
	bool oneshot_play = false;
	//! Stop this sample
	bool oneshot_stop = false;
	//! \}

private:
	//! AudioSystem::ComponentPrivate
	Private private_data;
};

} // namespace crepe
