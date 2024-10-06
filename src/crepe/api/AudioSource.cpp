#include "AudioSource.h"

#include "../Sound.h"
#include <memory>

using namespace crepe::api;

AudioSource::AudioSource(std::unique_ptr<Asset> audio_clip) {
	this->_sound = std::make_unique<crepe::Sound>(std::move(audio_clip));
}

void AudioSource::play() { return this->play(false); }

void AudioSource::play(bool looping) {
	this->_sound->set_looping(looping);
	this->_sound->play();
}

void AudioSource::stop() {
	this->_sound->pause();
	this->_sound->rewind();
}
