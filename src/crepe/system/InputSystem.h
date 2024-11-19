#pragma once

#include "System.h"
#include "../api/Event.h"
namespace crepe {

class InputSystem : public System {
public:
	using System::System;
	InputSystem(ComponentManager & component_manager);
	void update() override;
	bool handle_click(const MouseClickEvent &event);
	bool handle_move(const MouseMoveEvent &event);
	bool handle_key_press(const KeyPressEvent &event);
	bool handle_key_release(const KeyReleaseEvent &event);
};

} // namespace crepe
