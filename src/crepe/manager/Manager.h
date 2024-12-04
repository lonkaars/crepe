#pragma once

#include "Mediator.h"

namespace crepe {

/**
 * \brief Base manager class
 *
 * Managers are used for various tasks that fall outside the ECS system category. All managers
 * are required to register themselves to the mediator passed to the constructor, and this
 * mutable reference is saved for convenience, even though not all managers use the mediator
 * directly.
 */
class Manager {
public:
	Manager(Mediator & mediator);
	virtual ~Manager() = default;

protected:
	Mediator & mediator;
};

} // namespace crepe
