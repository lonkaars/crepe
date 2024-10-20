#include "Rigidbody.h"

using namespace crepe;

Rigidbody::Rigidbody(uint32_t gameObjectId,int mass, int gravityScale, BodyType bodyType)
	: Component(gameObjectId), mass(mass), gravity_scale(gravityScale), body_type(bodyType) {}

