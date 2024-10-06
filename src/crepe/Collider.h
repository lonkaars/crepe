#pragma once

#include "Component.h"

namespace crepe {

class Collider : public Component {
public:
	Collider(int size);

	int size;
};

}

