#pragma once

#include "Component.h"
#include "api/Vector2.h"

namespace crepe {

class Collider : public Component {
public:
	Collider(game_object_id_t id, Vector2 offset);
	Vector2 offset;
};

} // namespace crepe
