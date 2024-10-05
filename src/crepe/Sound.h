#pragma once

#include <soloud.h>
#include <soloud_wav.h>

#include <memory>

#include "api/Asset.h"

namespace crepe {

class Sound {
public:
	/**
	 * \brief Pause this sample
	 *
	 * Pauses this sound if it is playing, or does nothing if it is already
	 * paused. The playhead position is saved, such that calling \c play() after
	 * this function makes the sound resume.
	 */
	void pause();
	/**
	 * \brief Play this sample
	 *
	 * Resume playback if this sound is paused, or start from the beginning of
	 * the sample.
	 *
	 * \note This class only saves a reference to the most recent 'voice' of this
	 * sound. Calling \c play() while the sound is already playing causes
	 * multiple instances of the sample to play simultaniously. The sample
	 * started last is the one that is controlled afterwards.
	 */
	void play();
	/**
	 * \brief Reset playhead position
	 * 
	 * Resets the playhead position so that calling \c play() after this function
	 * makes it play from the start of the sample. If the sound is not paused
	 * before calling this function, this function will stop playback.
	 */
	void rewind();
	/**
	 * \brief Set playback volume / gain
	 *
	 * \param volume  Volume (0 = muted, 1 = full volume)
	 */
	void set_volume(float volume);
	/**
	 * \brief Get playback volume / gain
	 *
	 * \return Volume
	 */
	float get_volume() const { return this->volume; }
	/**
	 * \brief Set looping behavior for this sample
	 *
	 * \param looping  Looping behavior (false = one-shot, true = loop)
	 */
	void set_looping(bool looping);
	/**
	 * \brief Get looping behavior
	 *
	 * \return true if looping, false if one-shot
	 */
	bool get_looping() const { return this->looping; }

public:
	Sound(const char * src);
	Sound(std::unique_ptr<api::Asset> res);

private:
	void load(std::unique_ptr<api::Asset> res);

private:
	SoLoud::Wav sample;
	SoLoud::handle handle;

	float volume = 1.0f;
	bool looping = false;
};

} // namespace crepe
