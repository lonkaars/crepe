#pragma once

#include "System.h"

#include "../manager/LoopTimerManager.h"

namespace crepe {

class Script;

/**
 * \brief Script system
 *
 * The script system is responsible for all \c BehaviorScript components, and
 * calls the methods on classes derived from \c Script.
 */
class ScriptSystem : public System {
public:
	using System::System;
	/**
	 * \brief Call Script::fixed_update() on all active \c BehaviorScript instances
	 *
	 * This routine updates all scripts sequentially using the Script::update()
	 * method. It also calls Script::init() if this has not been done before on
	 * the \c BehaviorScript instance.
	 */
	void fixed_update() override;

	/**
	 * \brief Call Script::frame_update() on all active \c BehaviorScript instances
	 *
	 * This routine updates all scripts sequentially using the Script::update()
	 * method. It also calls Script::init() if this has not been done before on
	 * the \c BehaviorScript instance.
	 */
	void frame_update() override;

private:
	void update(void (Script::*update_function)(duration_t), const duration_t & delta_time);
};

} // namespace crepe
