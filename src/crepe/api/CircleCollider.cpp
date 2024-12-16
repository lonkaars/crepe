#include "CircleCollider.h"

using namespace crepe;

CircleCollider::CircleCollider(game_object_id_t game_object_id, float radius,
							   const vec2 & offset)
	: Collider(game_object_id, offset),
	  radius(radius) {}
