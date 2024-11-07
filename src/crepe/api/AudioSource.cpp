#include <memory>

#include "AudioSource.h"

using namespace crepe;
using namespace std;

AudioSource::AudioSource(game_object_id_t id, unique_ptr<Asset> audio_clip) :
	Component(id),
	audio_clip(std::move(audio_clip))
{ }

void AudioSource::play(bool looping) {
	this->loop = looping;
	this->playing = true;
}

void AudioSource::stop() {
	this->playing = false;
	this->rewind = true;
}

