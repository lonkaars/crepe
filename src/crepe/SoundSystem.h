#pragma once

#include <soloud.h>

#include <memory>

#include "Sound.h"

namespace crepe {

class SoundSystem {
public:
	static std::unique_ptr<Sound> sound(const std::string & res);
	static std::unique_ptr<Sound> sound(std::unique_ptr<api::Resource> res);

private:
	SoundSystem();
	virtual ~SoundSystem();

	// singleton
	static SoundSystem & instance();
	SoundSystem(const SoundSystem &) = delete;
	SoundSystem(SoundSystem &&) = delete;
	SoundSystem &operator=(const SoundSystem &) = delete;
	SoundSystem &operator=(SoundSystem &&) = delete;

private:
	SoLoud::Soloud engine;
	friend class Sound;
};

}

