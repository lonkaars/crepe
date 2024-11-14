#include <memory>

#include "../Asset.h"
#include "../util/Log.h"

#include "Sound.h"
#include "SoundContext.h"

using namespace crepe;
using namespace std;

Sound::Sound(SoundContext & ctx) : context(ctx) { dbg_trace(); }

unique_ptr<Resource> Sound::clone(const Asset & src) const {
	auto instance = make_unique<Sound>(*this);
	instance->sample.load(src.get_canonical().c_str());
	return instance;
}

void Sound::play() {
	SoundContext & ctx = this->context;
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
	SoundContext & ctx = this->context;
	if (ctx.engine.getPause(this->handle)) return;
	ctx.engine.setPause(this->handle, true);
}

void Sound::rewind() {
	SoundContext & ctx = this->context;
	if (!ctx.engine.isValidVoiceHandle(this->handle)) return;
	ctx.engine.seek(this->handle, 0);
}

void Sound::set_volume(float volume) {
	this->volume = volume;

	SoundContext & ctx = this->context;
	if (!ctx.engine.isValidVoiceHandle(this->handle)) return;
	ctx.engine.setVolume(this->handle, this->volume);
}

void Sound::set_looping(bool looping) {
	this->looping = looping;

	SoundContext & ctx = this->context;
	if (!ctx.engine.isValidVoiceHandle(this->handle)) return;
	ctx.engine.setLooping(this->handle, this->looping);
}
