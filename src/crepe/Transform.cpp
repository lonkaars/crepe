#include "Transform.h"

using namespace crepe;

Transform::Transform(uint32_t gameObjectId,int mass, int gravityScale, int bodyType)
	: Component(gameObjectId), mass(mass), gravity_scale(gravityScale), body_type(bodyType) {}
