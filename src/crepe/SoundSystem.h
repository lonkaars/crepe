#pragma once

#include <soloud.h>

#include "Sound.h"

namespace crepe {

class SoundSystem {
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

