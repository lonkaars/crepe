#include "AudioSource.h"

using namespace crepe;
using namespace std;

AudioSource::AudioSource(game_object_id_t id, const Asset & src) :
	Component(id),
	source(src)
{ }

void AudioSource::play(bool looping) {
	this->loop = looping;
	this->playing = true;
}

void AudioSource::stop() {
	this->playing = false;
	this->rewind = true;
}

