#include "Button.h"

namespace crepe {

Button::Button(game_object_id_t id, int width, int height, bool is_toggle, std::function<void()> on_click)
    : UiObject(id, width, height), is_toggle(is_toggle), is_pressed(false), hover(false), on_click(on_click) {}

} // namespace crepe
