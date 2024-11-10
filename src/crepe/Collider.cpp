#include "Collider.h"

using namespace crepe;

Collider::Collider(game_object_id_t id, Vector2 offset) : Component(id), offset(offset) {}
