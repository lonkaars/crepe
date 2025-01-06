#pragma once

#include "../manager/Mediator.h"

namespace crepe {

class ComponentManager;

/**
 * \brief Base ECS system class
 *
 * This class is used as the base for all system classes. Classes derived from System must
 * implement the System::update() method and copy Script::Script with the `using`-syntax.
 */
class System {
public:
	//! Code that runs in the fixed loop
	virtual void fixed_update() {};
	//! Code that runs in the frame loop
	virtual void frame_update() {};
	//! Indicates that the update functions of this system should be run
	bool active = true;

public:
	System(const Mediator & m);
	virtual ~System() = default;

protected:
	const Mediator & mediator;
};

} // namespace crepe
