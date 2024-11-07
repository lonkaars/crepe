#include "Rigidbody.h"

using namespace crepe;

Rigidbody::Rigidbody(game_object_id_t id, int mass, int gravity_scale,
					 BodyType bodyType)
	: Component(id), mass(mass), gravity_scale(gravity_scale),
	  body_type(bodyType) {}
