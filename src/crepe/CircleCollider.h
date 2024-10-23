#pragma once
#include "Collider.h"

namespace crepe {

class CircleCollider : public Collider {
public:
	CircleCollider(uint32_t gameObjectId,int radius) : Collider(gameObjectId), radius(radius) {}
	int radius;
};

} // namespace crepe
