#include "SoundSystem.h"
#include <memory>

using namespace crepe;

SoundSystem SoundSystem::instance { };

std::unique_ptr<Sound> SoundSystem::sound(const std::string & src) {
	auto res = std::make_unique<api::Resource>(src);
	return SoundSystem::sound(std::move(res));
}

std::unique_ptr<Sound> SoundSystem::sound(std::unique_ptr<api::Resource> res) {
	Sound * out = new Sound(std::move(res), SoundSystem::instance);
	return std::unique_ptr<Sound>(out);
}

SoundSystem::SoundSystem() {
	engine.init();
}

SoundSystem::~SoundSystem() {
	engine.deinit();
}

