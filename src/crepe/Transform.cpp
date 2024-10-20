#include "Transform.h"

using namespace crepe;

Transform::Transform(int mass, int gravityScale, int bodyType)
	: mass(mass), gravity_scale(gravityScale), body_type(bodyType) {}
