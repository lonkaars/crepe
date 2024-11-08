#pragma once

#include "Component.h"

namespace crepe {

class Collider : public Component {
public:
	Collider(game_object_id_t id);

	int size;
};

} // namespace crepe
