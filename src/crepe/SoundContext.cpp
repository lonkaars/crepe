#include "util/log.h"

#include "SoundSystem.h"

using namespace crepe;

SoundSystem & SoundSystem::get_instance() {
	static SoundSystem instance;
	return instance;
}

SoundSystem::SoundSystem() {
	dbg_trace();
	engine.init();
}

SoundSystem::~SoundSystem() {
	dbg_trace();
	engine.deinit();
}

