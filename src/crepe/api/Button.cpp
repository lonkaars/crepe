#include "Button.h"

namespace crepe {

Button::Button(
	game_object_id_t id, const vec2 & dimensions, const vec2 & offset, const Data & data
)
	: UIObject(id, dimensions, offset),
	  data(data) {}

} // namespace crepe
