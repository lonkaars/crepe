#pragma once

#include "../manager/Mediator.h"

namespace crepe {

class ComponentManager;

/**
 * \brief Base ECS system class
 *
 * This class is used as the base for all system classes. Classes derived from
 * System must implement the System::update() method and copy Script::Script
 * with the `using`-syntax.
 */
class System {
public:
	/**
	 * \brief Process all components this system is responsible for.
	 */
	virtual void update() = 0;

public:
	System(const Mediator & m);
	virtual ~System() = default;

protected:
	const Mediator & mediator;
};

} // namespace crepe
