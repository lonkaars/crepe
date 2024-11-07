#include "Rigidbody.h"

using namespace crepe;

Rigidbody::Rigidbody(uint32_t game_object_id, int mass, int gravity_scale,
					 BodyType bodyType)
	: Component(game_object_id), mass(mass), gravity_scale(gravity_scale),
	  body_type(bodyType) {}
