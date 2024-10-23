#include "Rigidbody.h"

using namespace crepe::api;

Rigidbody::Rigidbody(int mass, int gravityScale, int bodyType)
	: mass(mass), gravity_scale(gravityScale), body_type(bodyType) {}
