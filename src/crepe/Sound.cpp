#include "util/log.h"

#include "Sound.h"
#include "SoundSystem.h"

using namespace crepe;

Sound::Sound(std::unique_ptr<api::Resource> res) {
	dbg_trace();
	this->load(std::move(res));
}

Sound::Sound(const char * src) {
	dbg_trace();
	this->load(std::make_unique<api::Resource>(src));
}

void Sound::load(std::unique_ptr<api::Resource> res) {
	this->sample.load(res->canonical());
}

void Sound::play() {
	SoundSystem & system = SoundSystem::instance();
	if (system.engine.getPause(this->handle)) {
		// resume if paused
		system.engine.setPause(this->handle, false);
	} else {
		// or start new sound
		this->handle = system.engine.play(this->sample);
	}
}

void Sound::pause() {
	SoundSystem & system = SoundSystem::instance();
	if (system.engine.getPause(this->handle)) return;
	system.engine.setPause(this->handle, true);
}

