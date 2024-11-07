#pragma once

#include <memory>

#include "../Asset.h"
#include "../Component.h"
#include "../types.h"

namespace crepe {

//! Audio source component
class AudioSource : public Component {
public:
	AudioSource(game_object_id_t id, std::unique_ptr<Asset> audio_clip);
	virtual ~AudioSource() = default;

public:
	//! Start or resume this audio source
	void play(bool looping = false);
	//! Stop this audio source
	void stop();

public:
	//! Sample file location
	const std::unique_ptr<Asset> audio_clip;
	//! Play when this component becomes active
	bool play_on_awake = false;
	//! Repeat the current audio clip during playback
	bool loop = false;
	//! Normalized volume (0.0 - 1.0)
	float volume = 1.0;

private:
	//! If this source is playing audio
	bool playing = false;
	//! Rewind the sample location
	bool rewind = false;

private:
	//! Value of \c active after last system update
	bool last_active = false;
	//! Value of \c playing after last system update
	bool last_playing = false;
	//! Value of \c volume after last system update
	float last_volume = 1.0;
	//! Value of \c loop after last system update
	bool last_loop = false;
};

} // namespace crepe

