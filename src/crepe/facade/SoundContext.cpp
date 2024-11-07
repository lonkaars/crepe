#include "../util/log.h"

#include "SoundContext.h"

using namespace crepe;

SoundContext & SoundContext::get_instance() {
	static SoundContext instance;
	return instance;
}

SoundContext::SoundContext() {
	dbg_trace();
	engine.init();
}

SoundContext::~SoundContext() {
	dbg_trace();
	engine.deinit();
}
