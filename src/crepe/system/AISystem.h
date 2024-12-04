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
	bool accumulate_force(vec2 & running_total, vec2 force_to_add);

	vec2 seek(const AI & ai);
};

} // namespace crepe
