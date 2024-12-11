#include "Component.h"

using namespace crepe;

Component::Component(game_object_id_t id) : game_object_id(id) {}

Component & Component::operator=(const Component &) {
	return *this;
}

