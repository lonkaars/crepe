#include "CircleCollider.h"

using namespace crepe;


CircleCollider::CircleCollider(game_object_id_t game_object_id,Vector2 offset, int radius) : Collider(game_object_id,offset), radius(radius) {}
