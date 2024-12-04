#include "UIObject.h"

using namespace crepe;

UIObject::UIObject(game_object_id_t id, const vec2 & dimensions, const vec2 &offset)
	: Component(id),
	  dimensions(dimensions),
	  offset(offset) {}
