#pragma once

#include "../api/AudioSource.h"
#include "../facade/Sound.h"
#include "../facade/SoundContext.h"

#include "System.h"

namespace crepe {

class AudioSystem : public System {
public:
	using System::System;
	void update() override;

private:
	//! Private data stored by AudioSystem on AudioSource component
	struct ComponentPrivate {
		//! This sample's voice handle
		Sound::Handle handle;

		/**
		 * \name State diffing variables
		 * \{
		 */
		typeof(AudioSource::active) last_active;
		typeof(AudioSource::volume) last_volume;
		typeof(AudioSource::loop) last_loop;
		//! \}
	};

	/**
	 * \brief Update `last_*` members of \c data
	 *
	 * Copies all component properties stored for comparison between AudioSystem::update() calls
	 *
	 * \param component Source properties
	 * \param data Destination properties
	 */
	void update_last(const AudioSource & component, ComponentPrivate & data);

	/**
	 * \brief Compare update component
	 *
	 * Compares properties of \c component and \c data, and calls SoundContext functions where
	 * applicable.
	 *
	 * \param component AudioSource component to update
	 * \param data AudioSource's private data
	 * \param resource Sound instance for AudioSource's Asset
	 */
	void diff_update(AudioSource & component, ComponentPrivate & data, Sound & resource);

protected:
	/**
	 * \brief Get SoundContext
	 *
	 * SoundContext is retrieved through this function instead of being a direct member of
	 * AudioSystem to aid with testability.
	 */
	virtual SoundContext & get_context();

private:
	//! Actually stores SoundContext if the base AudioSystem::get_context implementation is used
	Private context;
};

} // namespace crepe
