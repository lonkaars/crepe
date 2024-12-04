#pragma once

#include "api/AI.h"

#include "System.h"
#include "types.h"

namespace crepe {

class AISystem : public System {
public:
	using System::System;

	void update() override;

private:
	vec2 calculate(AI & ai);
};

} // namespace crepe
