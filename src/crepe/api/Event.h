#pragma once
// TODO discussing the location of these events

#include <string>

#include "api/KeyCodes.h"
#include "types.h"

namespace crepe {

/**
 * \brief Base class for all event types in the system.
 */
class Event {};

/**
 * \brief Event triggered when a key is pressed.
 */
class KeyPressEvent : public Event {
public:
	//! false if first time press, true if key is repeated
	bool repeat = false;

	//! The key that was pressed.
	Keycode key = Keycode::NONE;
};

/**
 * \brief Event triggered when a key is released.
 */
class KeyReleaseEvent : public Event {
public:
	//! The key that was released.
	Keycode key = Keycode::NONE;
};

/**
 * \brief Event triggered when a mouse button is pressed.
 */
class MousePressEvent : public Event {
public:
	//! mouse position in game units
	vec2 mouse_pos = {0, 0};

	//! The mouse button that was pressed.
	MouseButton button = MouseButton::NONE;
};

/**
 * \brief Event triggered when a mouse button is clicked (press and release).
 */
class MouseClickEvent : public Event {
public:
	//! mouse position in game units
	vec2 mouse_pos = {0, 0};

	//! The mouse button that was clicked.
	MouseButton button = MouseButton::NONE;
};

/**
 * \brief Event triggered when a mouse button is released.
 */
class MouseReleaseEvent : public Event {
public:
	//! mouse position in game units
	vec2 mouse_pos = {0, 0};

	//! The mouse button that was released.
	MouseButton button = MouseButton::NONE;
};

/**
 * \brief Event triggered when the mouse is moved.
 */
class MouseMoveEvent : public Event {
public:
	//! mouse position in game units
	vec2 mouse_pos = {0, 0};
	//! The change in mouse position relative to the last position (in pixels).
	ivec2 mouse_delta = {0, 0};
};

/**
 * \brief Event triggered when the mouse is moved.
 */
class MouseScrollEvent : public Event {
public:
	//! mouse position in game units when the scroll happened.
	vec2 mouse_pos = {0, 0};
	//! scroll direction (-1 = down, 1 = up)
	int scroll_direction = 0;
	//! scroll amount in y axis (from and away from the person).
	float scroll_delta = 0;
};

/**
 * \brief Event triggered when text is submitted, e.g., from a text input.
 */
class TextSubmitEvent : public Event {
public:
	//! The submitted text.
	std::string text = "";
};

/**
 * \brief Event triggered to indicate the application is shutting down.
 */
class ShutDownEvent : public Event {};

/**
 * \brief Event triggered to indicate the window is overlapped by another window.
 * 
 * When two windows overlap the bottom window gets distorted and that window has to be redrawn.
 */
class WindowExposeEvent : public Event {};

/**
 * \brief Event triggered to indicate the window is resized.
 */
class WindowResizeEvent : public Event {
public:
	//! new window dimensions
	ivec2 dimensions = {0, 0};
};

/**
 * \brief Event triggered to indicate the window is moved.
 */
class WindowMoveEvent : public Event {
public:
	//! The change in position relative to the last position (in pixels).
	ivec2 delta_move = {0, 0};
};

/**
 * \brief Event triggered to indicate the window is minimized.
 */
class WindowMinimizeEvent : public Event {};

/**
 * \brief Event triggered to indicate the window is maximized
 */
class WindowMaximizeEvent : public Event {};

/**
 * \brief Event triggered to indicate the window gained focus
 * 
 * This event is triggered when the window receives focus, meaning it becomes the active window
 * for user interaction.
 */
class WindowFocusGainEvent : public Event {};

/**
 * \brief Event triggered to indicate the window lost focus
 * 
 * This event is triggered when the window loses focus, meaning it is no longer the active window
 * for user interaction.
 */
class WindowFocusLostEvent : public Event {};

} // namespace crepe
