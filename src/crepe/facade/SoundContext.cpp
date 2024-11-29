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
		.handle = this->engine.play(resource.sample, this->default_volume),
	};
}

void SoundContext::stop(Sound::Handle & handle) {
	this->engine.stop(handle.handle);
}

void SoundContext::set_volume(Sound & resource, Sound::Handle & handle, float volume) {
	this->engine.setVolume(handle.handle, volume);
	this->default_volume = volume;
}

void SoundContext::set_loop(Sound & resource, Sound::Handle & handle, bool loop) {
	this->engine.setLooping(handle.handle, loop);
}

bool SoundContext::get_playing(Sound::Handle & handle) {
	// See Soloud::stopVoice_internal in soloud/src/core/soloud_core_voiceops.cpp for why this is
	// the correct method to use here (samples are currently never paused)
	return this->engine.isValidVoiceHandle(handle.handle);
}

