#pragma once

#include "../ComponentManager.h"

namespace crepe {

//! ECS system base class
class System {
public:
	//! Process components belonging to this system
	virtual void update() = 0;

public:
	System();
	virtual ~System() = default;

public:
	//! Reference to component manager
	ComponentManager & compmgr;
};

} // namespace crepe
