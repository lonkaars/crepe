#include "BoxCollider.h"
#include "../Collider.h" 

using namespace crepe;


BoxCollider::BoxCollider(game_object_id_t game_object_id,vec2 offset, double width, double height) : Collider(game_object_id,offset), width(width), height(height) {}
