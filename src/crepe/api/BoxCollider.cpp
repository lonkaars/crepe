#include "BoxCollider.h"

#include "../Collider.h" 

using namespace crepe;

BoxCollider::BoxCollider(game_object_id_t game_object_id,vec2 offset, float width, float height) : Collider(game_object_id,offset), width(width), height(height) {}
