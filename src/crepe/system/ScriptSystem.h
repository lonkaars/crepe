#pragma once

#include "../manager/LoopTimerManager.h"

#include "System.h"

namespace crepe {

class Script;

/**
 * \brief Script system
 *
 * The script system is responsible for all \c BehaviorScript components, and calls the methods
 * on classes derived from \c Script.
 */
class ScriptSystem : public System {
public:
	using System::System;

public:
	//! Call Script::fixed_update() on all active \c BehaviorScript instances
	void fixed_update() override;
	//! Call Script::frame_update() on all active \c BehaviorScript instances
	void frame_update() override;

private:
	/**
	 * \brief Call Script `*_update` member function on all active \c BehaviorScript instances
	 *
	 * \note This routine also calls Script::init() if this has not been done before on the \c
	 * BehaviorScript instance.
	 */
	void update(void (Script::*update_function)(duration_t), const duration_t & delta_time);
};

} // namespace crepe
