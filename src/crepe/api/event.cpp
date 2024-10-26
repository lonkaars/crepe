#include "event.h"
#include "keyCodes.h"

using namespace crepe::api;

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
CollisionEvent::CollisionEvent(Collision collision)
	: collisionData(collision), Event("CollisionEvent") {}

Collision CollisionEvent::getCollisionData() const {
	return this->collisionData;
}
