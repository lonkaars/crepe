#include <memory>

#include "AudioSource.h"

#include "../Sound.h"

using namespace crepe::api;

AudioSource::AudioSource(std::unique_ptr<Asset> audio_clip) {
	this->sound = std::make_unique<crepe::Sound>(std::move(audio_clip));
}

void AudioSource::play() { return this->play(false); }

void AudioSource::play(bool looping) {
	this->sound->set_looping(looping);
	this->sound->play();
}

void AudioSource::stop() {
	this->sound->pause();
	this->sound->rewind();
}
