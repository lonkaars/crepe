#pragma once

#include "../Component.h"

namespace crepe::api {

class Collider : public Component {
public:
	Collider(uint32_t gameObjectId);

	int size;
};

} // namespace crepe::api
