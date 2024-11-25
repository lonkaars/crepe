#pragma once

#include <utility>

#include "System.h"

#include "../api/Event.h"
#include "../api/Button.h"
#include "../api/Transform.h"

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
	void handle_click(const MouseReleaseEvent);

    Transform* find_transform_for_button(Button &button, std::vector<std::reference_wrapper<Transform>> &transforms);

    bool is_mouse_inside_button(const MouseReleaseEvent &event, const Button &button, const Transform &transform);

    void handle_button_press(Button &button, const MouseReleaseEvent &event);
};

} // namespace crepe
