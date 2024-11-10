#pragma once

#include "BoxCollider.h"

using namespace crepe;


BoxCollider::BoxCollider(game_object_id_t game_object_id,Vector2 offset, int width, int height) : Collider(game_object_id,offset), width(width), height(height) {}
