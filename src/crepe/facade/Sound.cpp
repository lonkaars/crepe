#include "../util/log.h"

#include "Sound.h"
#include "SoundContext.h"

using namespace crepe;

Sound::Sound(std::unique_ptr<Asset> res) {
	dbg_trace();
	this->load(std::move(res));
}

Sound::Sound(const char * src) {
	dbg_trace();
	this->load(std::make_unique<Asset>(src));
}

void Sound::load(std::unique_ptr<Asset> res) { this->sample.load(res->canonical()); }

void Sound::play() {
	SoundContext & ctx = SoundContext::get_instance();
	if (ctx.engine.getPause(this->handle)) {
		// resume if paused
		ctx.engine.setPause(this->handle, false);
	} else {
		// or start new sound
		this->handle = ctx.engine.play(this->sample, this->volume);
		ctx.engine.setLooping(this->handle, this->looping);
	}
}

void Sound::pause() {
	SoundContext & ctx = SoundContext::get_instance();
	if (ctx.engine.getPause(this->handle)) return;
	ctx.engine.setPause(this->handle, true);
}

void Sound::rewind() {
	SoundContext & ctx = SoundContext::get_instance();
	if (!ctx.engine.isValidVoiceHandle(this->handle)) return;
	ctx.engine.seek(this->handle, 0);
}

void Sound::set_volume(float volume) {
	this->volume = volume;

	SoundContext & ctx = SoundContext::get_instance();
	if (!ctx.engine.isValidVoiceHandle(this->handle)) return;
	ctx.engine.setVolume(this->handle, this->volume);
}

void Sound::set_looping(bool looping) {
	this->looping = looping;

	SoundContext & ctx = SoundContext::get_instance();
	if (!ctx.engine.isValidVoiceHandle(this->handle)) return;
	ctx.engine.setLooping(this->handle, this->looping);
}
