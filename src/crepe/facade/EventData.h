#pragma once
#include "../api/KeyCodes.h"
#include "../types.h"
namespace crepe {
//! EventType enum for passing eventType
	enum EventType {
		NONE = 0,
		MOUSE_DOWN,
		MOUSE_UP,
		MOUSE_MOVE,
		MOUSE_WHEEL,
		KEY_UP,
		KEY_DOWN,
		SHUTDOWN,
		WINDOW_MINIMIZE,
		WINDOW_MAXIMIZE,
		WINDOW_FOCUS_GAIN,
		WINDOW_FOCUS_LOST,
		WINDOW_MOVE,
		WINDOW_RESIZE,
		WINDOW_EXPOSE,
	};

	//! Struct for storing key data.
	struct KeyData {
		Keycode key = Keycode::NONE;
		bool key_repeat = false;
	};

	//! Struct for storing mouse data.
	struct MouseData {
		MouseButton mouse_button = MouseButton::NONE;
		ivec2 mouse_position = {-1, -1};
		int scroll_direction = -1;
		float scroll_delta = INFINITY;
		ivec2 rel_mouse_move = {-1, -1};
	};

	//! Struct for storing window data.
	struct WindowData {
		ivec2 move_delta;
		ivec2 resize_dimension;
	};
	
	//! EventData struct for passing event data from facade
	struct EventData {
	EventType event_type = EventType::NONE;
		union {
			KeyData key_data;
			MouseData mouse_data;
			WindowData window_data;
		} data;

	};
} // namespace crepe
