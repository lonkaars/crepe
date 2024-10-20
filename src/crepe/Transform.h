#pragma once

#include "Component.h"

namespace crepe {

class Transform : public Component {
public:
	Transform(uint32_t gameObjectId,int mass, int gravityScale, int bodyType);

	int mass;
	int gravity_scale;
	int body_type;
};

} // namespace crepe
