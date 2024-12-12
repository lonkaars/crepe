#include "BoxCollider.h"

#include "../Collider.h"

using namespace crepe;

BoxCollider::BoxCollider(game_object_id_t game_object_id, const vec2 & offset,
						 const vec2 & dimensions)
	: Collider(game_object_id, offset),
	  dimensions(dimensions) {}
