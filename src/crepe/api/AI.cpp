#include "AI.h"

namespace crepe {

AI::AI(game_object_id_t id, float mass, float max_speed, float max_force)
	: Component(id),
	  mass(mass),
	  max_speed(max_speed),
	  max_force(max_force) {}

} // namespace crepe
