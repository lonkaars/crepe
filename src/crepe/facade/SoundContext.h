#pragma once

#include <soloud/soloud.h>

#include "../api/Config.h"

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

	virtual Sound::Handle play(Sound & resource);
	virtual void stop(Sound::Handle &);
	virtual void set_volume(Sound &, Sound::Handle &, float);
	virtual void set_loop(Sound &, Sound::Handle &, bool);

private:
	SoLoud::Soloud engine;
	float default_volume = 1.0f;

	Config & config = Config::get_instance();
};

} // namespace crepe
