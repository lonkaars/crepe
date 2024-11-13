#pragma once

#include "Component.h"

namespace crepe {

class Collider : public Component {
public:
	using Component::Component;

	int size;
};

} // namespace crepe
