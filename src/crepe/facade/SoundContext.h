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
public:
	SoundContext();
	virtual ~SoundContext();

	SoundContext(const SoundContext &) = delete;
	SoundContext(SoundContext &&) = delete;
	SoundContext & operator=(const SoundContext &) = delete;
	SoundContext & operator=(SoundContext &&) = delete;


private:
	SoLoud::Soloud engine;
};

} // namespace crepe
