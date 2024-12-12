#include "Button.h"

namespace crepe {

Button::Button(game_object_id_t id, const vec2 & dimensions, const vec2 & offset,
			   const std::function<void()> & on_click, bool is_toggle)
	: UIObject(id, dimensions, offset),
	  is_toggle(is_toggle),
	  on_click(on_click) {}

} // namespace crepe
