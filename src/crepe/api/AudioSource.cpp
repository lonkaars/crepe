#include "AudioSource.h"

using namespace crepe;
using namespace std;

AudioSource::AudioSource(game_object_id_t id, const Asset & src)
	: Component(id),
	  source(src) {}

void AudioSource::play(bool looping) {
	this->loop = looping;
	this->oneshot_play = true;
}

void AudioSource::stop() { this->oneshot_stop = true; }
