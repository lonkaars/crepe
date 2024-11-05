#pragma once
#include "../Collider.h"

namespace crepe {

class CircleCollider : public Collider {
public:
	CircleCollider(uint32_t game_object_id, double radius)
		: Collider(game_object_id), radius(radius) {}
	double radius;
};

} // namespace crepe
