#pragma once

#include <soloud/soloud.h>
#include <soloud/soloud_wav.h>

#include "../Resource.h"

namespace crepe {

class SoundContext;

/**
 * \brief Sound resource facade
 *
 * This class is a wrapper around a \c SoLoud::Wav instance, which holds a
 * single sample. It is part of the sound facade.
 */
class Sound : public Resource {
public:
	Sound(const Asset & src);
	~Sound(); // dbg_trace

	class Handle {
	private:
		SoLoud::handle handle;
		float volume = 1.0f;
		bool looping = false;

		friend class SoundContext;
	};

private:
	SoLoud::Wav sample;

	friend class SoundContext;
};

} // namespace crepe
