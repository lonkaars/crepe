#pragma once

namespace crepe {

class PhysicsSystem {
public:
	PhysicsSystem();
	void update();
private:
	const double gravity = 1;
};

} // namespace crepe
