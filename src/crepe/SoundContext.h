#pragma once

#include <soloud.h>

#include "Sound.h"

namespace crepe {

class SoundContext {
private:
	SoundContext();
	virtual ~SoundContext();

	// singleton
	static SoundContext & get_instance();
	SoundContext(const SoundContext &) = delete;
	SoundContext(SoundContext &&) = delete;
	SoundContext &operator=(const SoundContext &) = delete;
	SoundContext &operator=(SoundContext &&) = delete;

private:
	SoLoud::Soloud engine;
	friend class Sound;
};

}

