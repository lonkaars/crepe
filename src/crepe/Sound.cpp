#include "Sound.h"
#include "SoundSystem.h"

using namespace crepe;

Sound::Sound(std::unique_ptr<api::Resource> res, SoundSystem & system) : system(system) {
	this->res = std::move(res);
}

void Sound::play() {
	if (this->system.engine.getPause(this->handle)) {
		// resume if paused
		this->system.engine.setPause(this->handle, false);
	} else {
		// or start new sound
		this->handle = this->system.engine.play(this->sample);
	}
}

void Sound::pause() {
	if (this->system.engine.getPause(this->handle)) return;
	this->system.engine.setPause(this->handle, true);
}

