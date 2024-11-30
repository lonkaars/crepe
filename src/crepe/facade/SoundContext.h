#pragma once

#include <soloud/soloud.h>

#include "../api/Config.h"

#include "Sound.h"

namespace crepe {

/**
 * \brief Sound engine facade
 *
 * This class is a wrapper around a \c SoLoud::Soloud instance, which provides the methods for
 * playing \c Sound instances. It is part of the sound facade.
 */
class SoundContext {
public:
	SoundContext();
	virtual ~SoundContext();

	SoundContext(const SoundContext &) = delete;
	SoundContext(SoundContext &&) = delete;
	SoundContext & operator=(const SoundContext &) = delete;
	SoundContext & operator=(SoundContext &&) = delete;

	/**
	 * \brief Play a sample
	 *
	 * Plays a Sound from the beginning of the sample and returns a handle to control it later.
	 *
	 * \param resource Sound instance to play
	 *
	 * \returns Handle to control this voice
	 */
	virtual Sound::Handle play(Sound & resource);
	/**
	 * \brief Stop a voice immediately if it is still playing
	 *
	 * \note This function does nothing if the handle is invalid or if the sound is already
	 * stopped / finished playing.
	 *
	 * \param handle Voice handle returned by SoundContext::play
	 */
	virtual void stop(Sound::Handle & handle);
	/**
	 * \brief Change the volume of a voice
	 *
	 * \note This function does nothing if the handle is invalid or if the sound is already
	 * stopped / finished playing.
	 *
	 * \param handle Voice handle returned by SoundContext::play
	 * \param volume New gain value (0=silent, 1=default)
	 */
	virtual void set_volume(Sound::Handle & handle, float volume);
	/**
	 * \brief Set the looping behavior of a voice
	 *
	 * \note This function does nothing if the handle is invalid or if the sound is already
	 * stopped / finished playing.
	 *
	 * \param handle Voice handle returned by SoundContext::play
	 * \param loop Looping behavior (false=oneshot, true=loop)
	 */
	virtual void set_loop(Sound::Handle & handle, bool loop);

private:
	//! Abstracted class
	SoLoud::Soloud engine;

	//! Config reference
	Config & config = Config::get_instance();
};

} // namespace crepe
