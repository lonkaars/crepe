#include "Component.h"

using namespace crepe;
using namespace std;

Component::Component(game_object_id_t id) : game_object_id(id) {}

Component & Component::operator=(const Component &) {
	return *this;
}

unique_ptr<Component> Component::save() const {
	return unique_ptr<Component>(new Component(*this));
}

void Component::restore(const Component & snapshot) {
	*this = snapshot;
}

