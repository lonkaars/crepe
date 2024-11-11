#pragma once
#include <typeindex>
//#include "keyCodes.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <variant>
using Keycode = uint16_t;
enum class MouseButton {
	NONE = 0,
	LEFT_MOUSE = 1,
	RIGHT_MOUSE = 2,
	MIDDLE_MOUSE = 3,
	X1_MOUSE = 4,
	X2_MOUSE = 5,
	SCROLL_UP = 6,
	SCROLL_DOWN = 7,
};
class Event {
public:
};

class KeyPressEvent : public Event {
public:
    int repeat = 0;
    Keycode key = 0;
};

class MouseClickEvent : public Event {
public:
    int mouse_x = 0;
    int mouse_y = 0;
    MouseButton button;
};
class KeyReleaseEvent : public Event {
public:
    Keycode key = 0;
};

class MousePressEvent : public Event {
public:
    int mouse_x = 0;
    int mouse_y = 0;
    MouseButton button;
};
class MouseReleaseEvent : public Event {
public:
    int mouse_x = 0;
    int mouse_y = 0;
    MouseButton button;
};
class MouseMoveEvent : public Event {
public:
    int mouse_x = 0;
    int mouse_y = 0;
};
class CollisionEvent : public Event{
public:
    //Collision collisionData;
};
class TextSubmitEvent : public Event{
public:
    std::string text;
};
class ShutDownEvent : public Event {
public:
};
