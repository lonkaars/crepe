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
	SoundSystem & system = SoundSystem::get_instance();
	if (system.engine.getPause(this->handle)) {
		// resume if paused
		system.engine.setPause(this->handle, false);
	} else {
		// or start new sound
		this->handle = system.engine.play(this->sample, this->volume);
		system.engine.setLooping(this->handle, this->looping);
	}
}

void Sound::pause() {
	SoundSystem & system = SoundSystem::get_instance();
	if (system.engine.getPause(this->handle)) return;
	system.engine.setPause(this->handle, true);
}

void Sound::rewind() {
	SoundSystem & system = SoundSystem::get_instance();
	if (!system.engine.isValidVoiceHandle(this->handle)) return;
	system.engine.seek(this->handle, 0);
}

void Sound::set_volume(float volume) {
	this->volume = volume;

	SoundSystem & system = SoundSystem::get_instance();
	if (!system.engine.isValidVoiceHandle(this->handle)) return;
	system.engine.setVolume(this->handle, this->volume);
}

void Sound::set_looping(bool looping) {
	this->looping = looping;

	SoundSystem & system = SoundSystem::get_instance();
	if (!system.engine.isValidVoiceHandle(this->handle)) return;
	system.engine.setLooping(this->handle, this->looping);
}

