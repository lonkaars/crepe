#pragma once

#include "../Component.h"
#include "../types.h"
#include "../facade/SoundHandle.h"

#include "Asset.h"
#include "GameObject.h"

namespace crepe {

class AudioSystem;

//! Audio source component
class AudioSource : public Component {
	//! AudioSource components are handled by AudioSystem
	friend class AudioSystem;

protected:
	/**
	 * \param source Sound sample to load
	 */
	AudioSource(game_object_id_t id, const Asset & source);
	//! Only ComponentManager creates components
	friend class ComponentManager;

public:
	// std::unique_ptr needs to be able to destoy this component
	virtual ~AudioSource() = default;

public:
	//! Start this audio source
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
	/**
	 * \name State diffing variables
	 * \{
	 */
	typeof(active) last_active = false;
	typeof(volume) last_volume = volume;
	typeof(loop) last_loop = loop;
	//! \}
	//! This source's voice handle
	SoundHandle voice{};

};

} // namespace crepe
