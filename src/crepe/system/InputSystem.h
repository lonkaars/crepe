#pragma once

#include "System.h"
#include "../api/Event.h"
namespace crepe {

class InputSystem : public System {
public:
	using System::System;
	void update() override;
	void process_events();
	
private:
	std::pair<int, int> last_mouse_down_position{-1, -1};
    MouseButton last_mouse_button = MouseButton::NONE;
	const int click_tolerance = 5;
	bool handle_click(const MouseClickEvent &event);
	bool handle_move(const MouseMoveEvent &event);
	bool handle_key_press(const KeyPressEvent &event);
	bool handle_key_release(const KeyReleaseEvent &event);
};

} // namespace crepe
