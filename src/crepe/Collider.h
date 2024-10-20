#pragma once

#include "Component.h"

namespace crepe {

class Collider : public Component {
public:
	Collider(uint32_t gameObjectId,int size);

	int size;
};

} // namespace crepe
