#pragma once

#include <memory>

#include "Asset.h"
#include "Component.h"

namespace crepe {
class Sound;
}

namespace crepe::api {

//! Audio source component
class AudioSource : Component {
public:
	AudioSource(std::unique_ptr<Asset> audio_clip);
	virtual ~AudioSource() = default;

public:
	//! Start or resume this audio source
	void play();
	void play(bool looping);
	//! Stop this audio source
	void stop();

public:
	//! Sample file location
	std::unique_ptr<Asset> audio_clip;
	//! TODO: ?????
	bool play_on_awake;
	//! Repeat the current audio clip during playback
	bool loop;
	//! Normalized volume (0.0 - 1.0)
	float volume;

private:
	std::unique_ptr<crepe::Sound> sound;
};

} // namespace crepe::api
