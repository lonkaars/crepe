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
	bool accumulate_force(AI & ai, vec2 & running_total, vec2 force_to_add);

	vec2 seek(const AI & ai);
	vec2 flee(const AI & ai);
	vec2 arrive(const AI & ai);
	vec2 path_follow(AI & ai);
};

} // namespace crepe
