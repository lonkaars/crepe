#pragma once

#include <soloud/soloud.h>
#include <soloud/soloud_wav.h>

#include "../Resource.h"

namespace crepe {

class SoundContext;

/**
 * \brief Sound resource facade
 *
 * This class is a wrapper around a \c SoLoud::Wav instance, which holds a single sample. It is
 * part of the sound facade.
 */
class Sound : public Resource {
public:
	Sound(const Asset & src);
	~Sound(); // dbg_trace

	//! Voice handle wrapper
	struct Handle {
		//! Voice handle (soloud), used by SoundContext
		SoLoud::handle handle;
	};

private:
	//! Deserialized resource (soloud)
	SoLoud::Wav sample;
	//! SoundContext uses \c sample
	friend class SoundContext;
};

} // namespace crepe
