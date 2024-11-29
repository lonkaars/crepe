#include "../api/Asset.h"
#include "../util/Log.h"

#include "Sound.h"
#include "SoundContext.h"

using namespace crepe;
using namespace std;

Sound::Sound(const Asset & src) : Resource(src) {
	this->sample.load(src.get_path().c_str());
	dbg_trace();
}
Sound::~Sound() { dbg_trace(); }

// void Sound::play(SoundContext & ctx) {
// 	if (ctx.engine.getPause(this->handle)) {
// 		// resume if paused
// 		ctx.engine.setPause(this->handle, false);
// 	} else {
// 		// or start new sound
// 		this->handle = ctx.engine.play(this->sample, this->volume);
// 		ctx.engine.setLooping(this->handle, this->looping);
// 	}
// }
// 
// void Sound::pause(SoundContext & ctx) {
// 	if (ctx.engine.getPause(this->handle)) return;
// 	ctx.engine.setPause(this->handle, true);
// }
// 
// void Sound::rewind(SoundContext & ctx) {
// 	if (!ctx.engine.isValidVoiceHandle(this->handle)) return;
// 	ctx.engine.seek(this->handle, 0);
// }
// 
// void Sound::set_volume(SoundContext & ctx, float volume) {
// 	this->volume = volume;
// 	if (!ctx.engine.isValidVoiceHandle(this->handle)) return;
// 	ctx.engine.setVolume(this->handle, this->volume);
// }
// 
// void Sound::set_looping(SoundContext & ctx, bool looping) {
// 	this->looping = looping;
// 	if (!ctx.engine.isValidVoiceHandle(this->handle)) return;
// 	ctx.engine.setLooping(this->handle, this->looping);
// }

