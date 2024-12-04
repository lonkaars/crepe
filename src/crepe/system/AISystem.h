#pragma once

#include "System.h"

namespace crepe {

class AISystem : public System {
public:
	using System::System;

	void update() override;
};

} // namespace crepe
