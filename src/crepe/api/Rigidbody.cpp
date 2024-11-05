#include "Rigidbody.h"

using namespace crepe;

crepe::Rigidbody::Rigidbody(uint32_t game_object_id,
							const RigidbodyData & data) :
	Component(game_object_id), data(data){}
