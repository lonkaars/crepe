#pragma once

#include "Vector2.h"

#include "../Collider.h"

namespace crepe {

class CircleCollider : public Collider {
public:
	CircleCollider(game_object_id_t game_object_id,Vector2 offset, int radius);
	double radius;
};

} // namespace crepe
