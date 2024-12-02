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

SoundHandle SoundContext::play(Sound & resource) {
	SoLoud::handle real_handle = this->engine.play(resource.sample, 1.0f);
	SoundHandle handle = this->next_handle;
	this->registry[handle] = real_handle;
	this->next_handle++;
	return handle;
}

void SoundContext::stop(const SoundHandle & handle) {
	this->engine.stop(this->registry[handle]);
}

void SoundContext::set_volume(const SoundHandle & handle, float volume) {
	this->engine.setVolume(this->registry[handle], volume);
}

void SoundContext::set_loop(const SoundHandle & handle, bool loop) {
	this->engine.setLooping(this->registry[handle], loop);
}

