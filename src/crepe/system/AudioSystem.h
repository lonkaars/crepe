#pragma once

#include "../facade/SoundContext.h"
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
		SoLoud::handle handle;

		//! Value of \c active after last system update
		bool last_active = false;
		//! Value of \c playing after last system update
		bool last_playing = false;
		//! Value of \c volume after last system update
		float last_volume = 1.0;
		//! Value of \c loop after last system update
		bool last_loop = false;
	};

	void update_private(const AudioSource & component, ComponentPrivate & data);

private:
	SoundContext context {};
};

} // namespace crepe

