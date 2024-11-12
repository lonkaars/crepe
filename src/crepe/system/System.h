#pragma once

namespace crepe {

class ComponentManager;

class System {
public:
	virtual void update() = 0;

public:
	System(ComponentManager &);
	virtual ~System() = default;

protected:
	ComponentManager & component_manager;
};

} // namespace crepe
