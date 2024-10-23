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

public:
	uint32_t gameObjectId;
	bool active;
};

} // namespace crepe
