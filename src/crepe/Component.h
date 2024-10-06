#pragma once

namespace crepe {

class Component {
public:
	Component();
	// TODO: shouldn't this constructor be deleted because this class will never
	// directly be instantiated?

	bool active;
};

} // namespace crepe
