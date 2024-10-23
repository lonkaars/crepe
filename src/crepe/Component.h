#pragma once

namespace crepe {

class Component {
protected:
	Component() = default;

public:
	virtual ~Component() = default;

public:
	bool active = true;
};

} // namespace crepe
