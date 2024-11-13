#pragma once

#include <soloud/soloud.h>

#include "Sound.h"

namespace crepe {

class SoundContext {
public:
	SoundContext();
	virtual ~SoundContext();

	SoundContext(const SoundContext &) = delete;
	SoundContext(SoundContext &&) = delete;
	SoundContext & operator=(const SoundContext &) = delete;
	SoundContext & operator=(SoundContext &&) = delete;

private:
	SoLoud::Soloud engine;
	//! Sound directly calls methods on \c engine
	friend class Sound;
};

} // namespace crepe
