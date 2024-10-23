#pragma once
#include <cstdint>

namespace crepe {

class Component {
protected:
	Component() = default;

public:
	Component(uint32_t id);
	virtual ~Component() {}
	// TODO: shouldn't this constructor be deleted because this class will never
	// directly be instantiated?
	//changed so it sets the id (jaro)
	uint32_t gameObjectId;
	bool active;
};

} // namespace crepe
