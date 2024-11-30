#include "../util/Log.h"

#include "SoundContext.h"

using namespace crepe;

SoundContext::SoundContext() {
	dbg_trace();
	this->engine.init();
	this->engine.setMaxActiveVoiceCount(this->config.audio.voices);
}

SoundContext::~SoundContext() {
	dbg_trace();
	this->engine.deinit();
}

Sound::Handle SoundContext::play(Sound & resource) {
	return {
		.handle = this->engine.play(resource.sample, 1.0f),
	};
}

void SoundContext::stop(Sound::Handle & handle) { this->engine.stop(handle.handle); }

void SoundContext::set_volume(Sound::Handle & handle, float volume) {
	this->engine.setVolume(handle.handle, volume);
}

void SoundContext::set_loop(Sound::Handle & handle, bool loop) {
	this->engine.setLooping(handle.handle, loop);
}
