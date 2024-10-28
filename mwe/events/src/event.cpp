#include "event.h"
#include "keyCodes.h"
// Event class methods
Event::Event(std::string eventType) { eventData["eventType"] = eventType; }

void Event::addArgument(const std::string & key,
						const std::variant<int, std::string, float> & value) {
	eventData[key] = value;
}

std::variant<int, std::string, float>
Event::getArgument(const std::string & key) const {
	return eventData.at(key);
}

std::string Event::getType() const {
	return std::get<std::string>(eventData.at("eventType"));
}
std::string Event::toString() const { return std::to_string(getEventType()); }
bool Event::getHandled() const { return isHandled; }

void Event::markHandled() { isHandled = true; }

// KeyPressedEvent class methods
KeyPressedEvent::KeyPressedEvent(int keycode)
	: Event("KeyPressedEvent"), key(keycode), repeatCount(0) {}

Keycode KeyPressedEvent::getKeyCode() const { return key; }

int KeyPressedEvent::getRepeatCount() const { return repeatCount; }

// KeyReleasedEvent class methods
KeyReleasedEvent::KeyReleasedEvent(int keycode)
	: Event("KeyReleasedEvent"), key(keycode) {}

Keycode KeyReleasedEvent::getKeyCode() const { return key; }

// MousePressedEvent class methods
MousePressedEvent::MousePressedEvent(int mouseX, int mouseY)
	: Event("MousePressedEvent"), mouseX(mouseX), mouseY(mouseY) {}

std::pair<int, int> MousePressedEvent::getMousePosition() const {
	return {mouseX, mouseY};
}

//Collision event
CollisionEvent::CollisionEvent(Collision collision) : collisionData(collision), Event("CollisionEvent") {

}

Collision CollisionEvent::getCollisionData() const
{
	return this->collisionData;
}

TextSubmitEvent::TextSubmitEvent(std::string text) 
    : text(text), Event("TextSubmitEvent") {}

std::string TextSubmitEvent::getText() const {
    return this->text;
}

MouseReleasedEvent::MouseReleasedEvent(int x, int y, MouseButton button) : mouseX(x), mouseY(y), button(button),Event("MouseReleased"){

}
std::pair<int, int> MouseReleasedEvent::getMousePosition() const{
	return {mouseX,mouseY};
}
MouseClickEvent::MouseClickEvent(int x,int y,MouseButton button) : mouseX(x), mouseY(y), button(button),Event("MouseClickEvent"){

}
MouseMovedEvent::MouseMovedEvent(int x, int y) : mouseX(x), mouseY(y),Event("MouseMovedEvent"){

}
std::pair<int, int> MouseClickEvent::getMousePosition() const {
	return {mouseX, mouseY};
}
std::pair<int, int> MouseMovedEvent::getMousePosition() const {
	return {mouseX, mouseY};
}
