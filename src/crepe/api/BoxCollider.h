#pragma once
#include "../Collider.h"

namespace crepe::api {

class BoxCollider : public Collider {
public:
	BoxCollider(uint32_t game_object_id, double width, double height)
		: Collider(game_object_id), width(width),height(height) {}
	double width;
	double height;
};

} // namespace crepe::api
