#pragma once

#include "Vector2.h"

#include "../Collider.h"

namespace crepe {

class CircleCollider : public Collider {
public:
<<<<<<< HEAD
	CircleCollider(game_object_id_t game_object_id,Vector2 offset, int radius);
	double radius;
=======
	CircleCollider(game_object_id_t game_object_id, int radius)
		: Collider(game_object_id),
		  radius(radius) {}
	int radius;
>>>>>>> be1e97bc7a494963ab1567492fafcda99e36f683
};

} // namespace crepe
