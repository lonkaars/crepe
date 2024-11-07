#pragma once

namespace crepe {

class System {
public:
	virtual void update() = 0;

public:
	System() = default;
	virtual ~System() = default;
};

} // namespace crepe
