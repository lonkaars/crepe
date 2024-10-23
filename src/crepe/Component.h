#pragma once
#include <cstdint>

namespace crepe {

class Component {
protected:
	Component(uint32_t id);

public:
	uint32_t gameObjectId;
	bool active;
	virtual ~Component() = default;
};

} // namespace crepe
