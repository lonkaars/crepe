#pragma once

#include "Vector2.h"
#include "../Collider.h"

namespace crepe {

class BoxCollider : public Collider {
public:
	BoxCollider(game_object_id_t game_object_id,Vector2 offset, double width, double height);
	double width;
	double height;
};

} // namespace crepe
