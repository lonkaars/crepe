#pragma once

#include "Component.h"

namespace crepe {

class Rigidbody : public Component {
public:
	Rigidbody(int mass, int gravityScale, int bodyType);

	int mass;
	int gravity_scale;
	int body_type;
};

}
