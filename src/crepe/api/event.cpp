#include "event.h"
#include "keyCodes.h"
// Event class methods
Event::Event() {}
std::string Event::toString() const { return std::to_string(getEventType()); }
bool Event::getHandled() const { return isHandled; }

void Event::markHandled() { isHandled = true; }

// KeyPressedEvent class methods
KeyPressedEvent::KeyPressedEvent(int keycode) : key(keycode), repeatCount(0) {}

Keycode KeyPressedEvent::getKeyCode() const { return key; }

int KeyPressedEvent::getRepeatCount() const { return repeatCount; }

// KeyReleasedEvent class methods
KeyReleasedEvent::KeyReleasedEvent(int keycode)
	: key(keycode) {}

Keycode KeyReleasedEvent::getKeyCode() const { return key; }

// MousePressedEvent class methods
MousePressedEvent::MousePressedEvent(int mouseX, int mouseY)
	: mouseX(mouseX), mouseY(mouseY) {}

std::pair<int, int> MousePressedEvent::getMousePosition() const {
	return {mouseX, mouseY};
}

//Collision event
CollisionEvent::CollisionEvent(Collision collision)
	: collisionData(collision) {}

Collision CollisionEvent::getCollisionData() const {
	return this->collisionData;
}

TextSubmitEvent::TextSubmitEvent(std::string text)
	: text(text) {}

std::string TextSubmitEvent::getText() const { return this->text; }

MouseReleasedEvent::MouseReleasedEvent(int x, int y, MouseButton button)
	: mouseX(x), mouseY(y), button(button) {}
std::pair<int, int> MouseReleasedEvent::getMousePosition() const {
	return {mouseX, mouseY};
}
MouseClickEvent::MouseClickEvent(int x, int y, MouseButton button)
	: mouseX(x), mouseY(y), button(button) {}
MouseMovedEvent::MouseMovedEvent(int x, int y)
	: mouseX(x), mouseY(y) {}
std::pair<int, int> MouseClickEvent::getMousePosition() const {
	return {mouseX, mouseY};
}
std::pair<int, int> MouseMovedEvent::getMousePosition() const {
	return {mouseX, mouseY};
}
