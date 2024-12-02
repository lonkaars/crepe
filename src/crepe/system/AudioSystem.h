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
	/**
	 * \brief Update `last_*` members of \c component
	 *
	 * Copies all component properties stored for comparison between AudioSystem::update() calls
	 *
	 * \param component AudioSource component to update
	 */
	void update_last(AudioSource & component);

	/**
	 * \brief Compare update component
	 *
	 * Compares properties of \c component and \c data, and calls SoundContext functions where
	 * applicable.
	 *
	 * \param component AudioSource component to update
	 * \param resource Sound instance for AudioSource's Asset
	 */
	void diff_update(AudioSource & component, Sound & resource);

protected:
	/**
	 * \brief Get SoundContext
	 *
	 * SoundContext is retrieved through this function instead of being a direct member of
	 * AudioSystem to aid with testability.
	 */
	virtual SoundContext & get_context();

private:
	//! SoundContext
	std::unique_ptr<SoundContext> context = nullptr;
};

} // namespace crepe
