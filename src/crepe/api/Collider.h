#pragma once

#include "../Component.h"

namespace crepe::api {

class Collider : public Component {
public:
	Collider(int size);

	int size;
};

} // namespace crepe::api
