#pragma once

#include "System.h"

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
	 * \brief Call Script::update() on all active \c BehaviorScript instances
	 *
	 * This routine updates all scripts sequentially using the Script::update()
	 * method. It also calls Script::init() if this has not been done before on
	 * the \c BehaviorScript instance.
	 */
	void update() override;
};

} // namespace crepe
