#pragma once
#include "../Collider.h"

namespace crepe {

class CircleCollider : public Collider {
public:
	CircleCollider(game_object_id_t game_object_id, int radius)
		: Collider(game_object_id), radius(radius) {}
	int radius;
};

} // namespace crepe
