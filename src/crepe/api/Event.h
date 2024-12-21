#pragma once
// TODO discussing the location of these events

#include <string>

#include "types.h"

#include "KeyCodes.h"

namespace crepe {

/**
 * \brief Base struct for all event types in the system.
 */
struct Event {};

/**
 * \brief Event triggered when a key is pressed.
 */
struct KeyPressEvent : public Event {
	//! false if first time press, true if key is repeated
	bool repeat = false;

	//! The key that was pressed.
	Keycode key = Keycode::NONE;
};

/**
 * \brief Event triggered when a key is released.
 */
struct KeyReleaseEvent : public Event {
	//! The key that was released.
	Keycode key = Keycode::NONE;
};

/**
 * \brief Event triggered when a mouse button is pressed.
 */
struct MousePressEvent : public Event {
	//! mouse position in world coordinates (game units).
	vec2 mouse_pos = {0, 0};

	//! The mouse button that was pressed.
	MouseButton button = MouseButton::NONE;
};

/**
 * \brief Event triggered when a mouse button is clicked (press and release).
 */
struct MouseClickEvent : public Event {
	//! mouse position in world coordinates (game units).
	vec2 mouse_pos = {0, 0};

	//! The mouse button that was clicked.
	MouseButton button = MouseButton::NONE;
};

/**
 * \brief Event triggered when a mouse button is released.
 */
struct MouseReleaseEvent : public Event {
	//! mouse position in world coordinates (game units).
	vec2 mouse_pos = {0, 0};

	//! The mouse button that was released.
	MouseButton button = MouseButton::NONE;
};

/**
 * \brief Event triggered when the mouse is moved.
 */
struct MouseMoveEvent : public Event {
	//! mouse position in world coordinates (game units).
	vec2 mouse_pos = {0, 0};
	//! The change in mouse position relative to the last position (in pixels).
	ivec2 mouse_delta = {0, 0};
};

/**
 * \brief Event triggered when the mouse is moved.
 */
struct MouseScrollEvent : public Event {
	//! mouse position in world coordinates (game units) when the scroll happened.
	vec2 mouse_pos = {0, 0};
	//! scroll direction (-1 = down, 1 = up)
	int scroll_direction = 0;
	//! scroll amount in y axis (from and away from the person).
	float scroll_delta = 0;
};

/**
 * \brief Event triggered to indicate the application is shutting down.
 */
struct ShutDownEvent : public Event {};

/**
 * \brief Event triggered to indicate the window is overlapped by another window.
 * 
 * When two windows overlap the bottom window gets distorted and that window has to be redrawn.
 */
struct WindowExposeEvent : public Event {};

/**
 * \brief Event triggered to indicate the window is resized.
 */
struct WindowResizeEvent : public Event {
	//! new window dimensions
	ivec2 dimensions = {0, 0};
};

/**
 * \brief Event triggered to indicate the window is moved.
 */
struct WindowMoveEvent : public Event {
	//! The change in position relative to the last position (in pixels).
	ivec2 delta_move = {0, 0};
};

/**
 * \brief Event triggered to indicate the window is minimized.
 */
struct WindowMinimizeEvent : public Event {};

/**
 * \brief Event triggered to indicate the window is maximized
 */
struct WindowMaximizeEvent : public Event {};

/**
 * \brief Event triggered to indicate the window gained focus
 * 
 * This event is triggered when the window receives focus, meaning it becomes the active window
 * for user interaction.
 */
struct WindowFocusGainEvent : public Event {};

/**
 * \brief Event triggered to indicate the window lost focus
 * 
 * This event is triggered when the window loses focus, meaning it is no longer the active window
 * for user interaction.
 */
struct WindowFocusLostEvent : public Event {};

} // namespace crepe
