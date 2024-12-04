#include "UiObject.h"

using namespace crepe;

UIObject::UIObject(game_object_id_t id, vec2 dimensions, vec2 offset)
	: Component(id),
	  dimensions(dimensions),
	  offset(offset) {}
