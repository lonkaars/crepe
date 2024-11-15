#pragma once
#include "KeyCodes.h"
#include <iostream>
#include <string>
#include <typeindex>

class Event {
public:
};

class KeyPressEvent : public Event {
public:
	int repeat = 0;
	Keycode key = Keycode::NONE;
};

class KeyReleaseEvent : public Event {
public:
	Keycode key = Keycode::NONE;
};

class MousePressEvent : public Event {
public:
	int mouse_x = 0;
	int mouse_y = 0;
	MouseButton button = MouseButton::NONE;
};

class MouseClickEvent : public Event {
public:
	int mouse_x = 0;
	int mouse_y = 0;
	MouseButton button = MouseButton::NONE;
};
class MouseReleaseEvent : public Event {
public:
	int mouse_x = 0;
	int mouse_y = 0;
	MouseButton button = MouseButton::NONE;
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
	std::string text = "";
};
class ShutDownEvent : public Event {
public:
};
