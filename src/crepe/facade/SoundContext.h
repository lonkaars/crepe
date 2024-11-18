#pragma once

#include <soloud/soloud.h>

#include "Sound.h"

namespace crepe {

/**
 * \brief Sound engine facade
 *
 * This class is a wrapper around a \c SoLoud::Soloud instance, which provides
 * the methods for playing \c Sound instances. It is part of the sound facade.
 */
class SoundContext {
private:
	// singleton
	SoundContext();
	virtual ~SoundContext();
	SoundContext(const SoundContext &) = delete;
	SoundContext(SoundContext &&) = delete;
	SoundContext & operator=(const SoundContext &) = delete;
	SoundContext & operator=(SoundContext &&) = delete;

private:
	static SoundContext & get_instance();
	SoLoud::Soloud engine;
	friend class Sound;
};

} // namespace crepe
