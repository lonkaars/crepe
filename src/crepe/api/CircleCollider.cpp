#include "CircleCollider.h"

using namespace crepe;


CircleCollider::CircleCollider(game_object_id_t game_object_id,const vec2& offset, float radius) : Collider(game_object_id,offset), radius(radius) {}
