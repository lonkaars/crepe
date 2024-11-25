#pragma once
// TODO discussing the location of these events

#include <string>

#include "KeyCodes.h"

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
	//! X-coordinate of the mouse position at the time of the event.
	int mouse_x = 0;

	//! Y-coordinate of the mouse position at the time of the event.
	int mouse_y = 0;

	//! The mouse button that was pressed.
	MouseButton button = MouseButton::NONE;
};

/**
 * \brief Event triggered when a mouse button is clicked (press and release).
 */
class MouseClickEvent : public Event {
public:
	//! X-coordinate of the mouse position at the time of the event.
	int mouse_x = 0;

	//! Y-coordinate of the mouse position at the time of the event.
	int mouse_y = 0;

	//! The mouse button that was clicked.
	MouseButton button = MouseButton::NONE;
};

/**
 * \brief Event triggered when a mouse button is released.
 */
class MouseReleaseEvent : public Event {
public:
	//! X-coordinate of the mouse position at the time of the event.
	int mouse_x = 0;

	//! Y-coordinate of the mouse position at the time of the event.
	int mouse_y = 0;

	//! The mouse button that was released.
	MouseButton button = MouseButton::NONE;
};

/**
 * \brief Event triggered when the mouse is moved.
 */
class MouseMoveEvent : public Event {
public:
	//! X-coordinate of the mouse position at the time of the event.
	int mouse_x = 0;

	//! Y-coordinate of the mouse position at the time of the event.
	int mouse_y = 0;
	// Relative movement in x
	int rel_x;
	// Relative movement in y
	int rel_y;
};

/**
 * \brief Event triggered when the mouse is moved.
 */
class MouseScrollEvent : public Event {
public:
	//! X-coordinate of the mouse position at the time of the event.
	int scroll_x = 0;

	//! Y-coordinate of the mouse position at the time of the event.
	int scroll_y = 0;
	int direction = 0;
};
/**
 * \brief Event triggered during a collision between objects.
 */
class CollisionEvent : public Event {};

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

} // namespace crepe
