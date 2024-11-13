#pragma once

#include "System.h"

namespace crepe {

class CollisionSystem : public System {
public:
	using System::System;
	void update() override;
};

} // namespace crepe
