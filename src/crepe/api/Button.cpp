#include "Button.h"

namespace crepe {

Button::Button(game_object_id_t id, int width, int height, std::function<void()> on_click, bool is_toggle
			   )
	: UiObject(id, width, height),
	  is_toggle(is_toggle),
	  on_click(on_click) {}

} // namespace crepe
