#pragma once

#include <forward_list>

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
	/**
	 * \brief Call Script::update() on all active \c BehaviorScript instances
	 *
	 * This routine updates all scripts sequentially using the Script::update()
	 * method. It also calls Script::init() if this has not been done before on
	 * the \c BehaviorScript instance.
	 */
	void update();

private:
	// TODO: to forward_list<reference_wrapper>
	/**
	 * \brief Aggregate all active \c BehaviorScript components and return a list
	 * of references to their \c Script instances (utility)
	 *
	 * \returns List of active \c Script instances
	 */
	std::forward_list<Script *> get_scripts() const;
};

} // namespace crepe
