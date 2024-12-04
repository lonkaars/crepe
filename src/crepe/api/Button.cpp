#include "Button.h"

namespace crepe {

Button::Button(game_object_id_t id, vec2 dimensions, vec2 offset,
			   std::function<void()> on_click, bool is_toggle)
	: UIObject(id, dimensions, offset),
	  is_toggle(is_toggle),
	  on_click(on_click) {}

} // namespace crepe
