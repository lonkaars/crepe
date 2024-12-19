#pragma once

#include "System.h"

namespace crepe {

/**
 * \brief EventManager dispatch helper system
 */
class EventSystem : public System {
public:
	using System::System;

	/**
	 * \brief Dispatch queued events
	 * \see EventManager::dispatch_events
	 */
	void fixed_update() override;
};

} // namespace crepe
