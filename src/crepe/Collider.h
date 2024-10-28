#pragma once

#include "Component.h"
#include "api/Rigidbody.h"

namespace crepe {

struct Collision {
    int objectIdA;          // ID of the first object
    int objectIdB;          // ID of the second object
    api::Vector2 contactPoint;   // Point of contact
    api::Vector2 contactNormal;  // Normal vector at the contact point
	
    // Constructor to initialize a Collision
    Collision(int idA, int idB, const api::Vector2& point, const api::Vector2& normal, float depth)
        : objectIdA(idA), objectIdB(idB), contactPoint(point), contactNormal(normal) {}

};

class Collider : public Component {
public:
	Collider(uint32_t game_object_id);

	int size;
};

} // namespace crepe
