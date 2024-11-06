#pragma once

#include <cstdint>

namespace crepe {

class ComponentManager;

class Component {
protected:
	friend class crepe::ComponentManager;
	Component(uint32_t id);

public:
	virtual ~Component() = default;
	virtual int get_instances_max() const { return -1; }

public:
	uint32_t game_object_id;
	bool active = true;
};

} // namespace crepe
