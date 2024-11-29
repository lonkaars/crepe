#pragma once

#include "../facade/SoundContext.h"
#include "../facade/Sound.h"
#include "../api/AudioSource.h"

#include "System.h"

namespace crepe {

class AudioSystem : public System {
public:
	using System::System;
	void update() override;

private:
	/**
	 * \brief Private data stored by AudioSystem on AudioSource component
	 */
	struct ComponentPrivate {
		//! This sample's voice handle
		Sound::Handle handle;

		/**
		 * \name State diffing variables
		 * \{
		 */
		typeof(AudioSource::active) last_active;
		typeof(AudioSource::playing) last_playing;
		typeof(AudioSource::volume) last_volume;
		typeof(AudioSource::loop) last_loop;
		//! \}
	};

	void update_last(const AudioSource & component, ComponentPrivate & data);

	void diff_update(AudioSource & component, ComponentPrivate & data, Sound & resource);

private:
	SoundContext context {};
};

} // namespace crepe

