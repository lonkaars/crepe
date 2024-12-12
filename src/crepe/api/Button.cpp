#include "Button.h"

namespace crepe {

Button::Button(game_object_id_t id, const vec2 & dimensions, const vec2 & offset,
			   const std::function<void()> & on_click)
	: UIObject(id, dimensions, offset),
	  on_click(on_click) {}

} // namespace crepe
