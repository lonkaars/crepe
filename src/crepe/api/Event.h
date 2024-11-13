#pragma once
#include <typeindex>
#include <iostream>
#include <string>
#include "KeyCodes.h"

class Event {
public:
	bool handled = false;
};

class KeyPressEvent : public Event {
public:
	int repeat = 0;
	Keycode key = Keycode::None;
};

class KeyReleaseEvent : public Event {
public:
	Keycode key = Keycode::None;
};

class MousePressEvent : public Event {
public:
	int mouse_x = 0;
	int mouse_y = 0;
	MouseButton button;
};

class MouseClickEvent : public Event {
public:
	int mouse_x = 0;
	int mouse_y = 0;
	MouseButton button;
};
class MouseReleaseEvent : public Event {
public:
	int mouse_x = 0;
	int mouse_y = 0;
	MouseButton button = MouseButton::None;
};
class MouseMoveEvent : public Event {
public:
	int mouse_x = 0;
	int mouse_y = 0;
};
class CollisionEvent : public Event {
public:
	//Collision collisionData;
};
class TextSubmitEvent : public Event {
public:
	std::string text;
};
class ShutDownEvent : public Event {
public:
};
