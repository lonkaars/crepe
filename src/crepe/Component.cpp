#include "Component.h"

using namespace crepe;

Component::Component(uint32_t id) : game_object_id(id), active(true) {}

int Component::get_instances_max() const { return -1; }
