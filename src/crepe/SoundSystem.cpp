#include "util/log.h"

#include "SoundSystem.h"
#include <memory>

using namespace crepe;

SoundSystem & SoundSystem::instance() {
	static SoundSystem instance;
	return instance;
}

std::unique_ptr<Sound> SoundSystem::sound(const std::string & src) {
	auto res = std::make_unique<api::Resource>(src);
	return SoundSystem::sound(std::move(res));
}

std::unique_ptr<Sound> SoundSystem::sound(std::unique_ptr<api::Resource> res) {
	Sound * out = new Sound(std::move(res));
	return std::unique_ptr<Sound>(out);
}

SoundSystem::SoundSystem() {
	dbg_trace();
	engine.init();
}

SoundSystem::~SoundSystem() {
	dbg_trace();
	engine.deinit();
}

