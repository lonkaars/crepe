#pragma once

namespace crepe {

class Component {
protected:
	Component() = default;
public:
	virtual ~Component() = default;
	// TODO: shouldn't this constructor be deleted because this class will never
	// directly be instantiated?

	bool active = true;
};

} // namespace crepe
