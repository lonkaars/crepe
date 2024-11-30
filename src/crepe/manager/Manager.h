#pragma once

#include "Mediator.h"

namespace crepe {

class Manager {
public:
	Manager(Mediator & mediator);
	virtual ~Manager() = default;

protected:
	Mediator & mediator;
};

} // namespace crepe
