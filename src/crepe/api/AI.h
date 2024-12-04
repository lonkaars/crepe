#pragma once

#include "Component.h"
#include "types.h"

namespace crepe {

class AI : public Component {
public:
	AI(game_object_id_t id, double mass, double max_speed, double max_force);

public:
	double mass;
	double max_speed;
	double max_force;
};

} // namespace crepe
