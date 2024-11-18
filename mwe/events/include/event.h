#pragma once
#include "customTypes.h"
#include "keyCodes.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <variant>
class UUIDGenerator {
public:
	static std::uint32_t getUniqueID() {
		static std::uint32_t id = 0;
		return ++id;
	}
};
#define REGISTER_EVENT_TYPE(ClassName) \
\
public: \
	static std::uint32_t getStaticEventType() { \
		static std::uint32_t typeID = UUIDGenerator::getUniqueID(); \
		return typeID; \
	} \
	virtual std::uint32_t getEventType() const override { return getStaticEventType(); }
class Event {
public:
	Event(std::string eventType);
	virtual ~Event() = default;
	virtual std::uint32_t getEventType() const = 0;
	virtual std::string toString() const;
	void addArgument(const std::string & key,
					 const std::variant<int, std::string, float> & value);

	std::variant<int, std::string, float> getArgument(const std::string & key) const;

	std::string getType() const;
	bool getHandled() const;
	void markHandled();

private:
	std::unordered_map<std::string, std::variant<int, std::string, float>> eventData;
	bool isHandled = false;
};

// KeyPressedEvent class
class KeyPressedEvent : public Event {
public:
	KeyPressedEvent(int keyCode);

	REGISTER_EVENT_TYPE("KeyPressedEvent");

	Keycode getKeyCode() const;
	int getRepeatCount() const;

private:
	Keycode keycode;

public:
	Keycode key = 0;
	int repeatCount = 0;
};
class MouseClickEvent : public Event {
public:
	MouseClickEvent(int x, int y, MouseButton button);

	REGISTER_EVENT_TYPE("KeyClickedEvent");
	std::pair<int, int> getMousePosition() const;
	MouseButton getButton() const { return button; }

private:
	int mouseX = 0;
	int mouseY = 0;
	MouseButton button;
};
// KeyReleasedEvent class
class KeyReleasedEvent : public Event {
public:
	KeyReleasedEvent(int keyCode);

	REGISTER_EVENT_TYPE(KeyReleasedEvent);

	Keycode getKeyCode() const;

private:
	Keycode key = 0;
};

// MousePressedEvent class
class MousePressedEvent : public Event {
public:
	MousePressedEvent(int mouseX, int mouseY);

	REGISTER_EVENT_TYPE(MousePressedEvent)

	std::pair<int, int> getMousePosition() const;

private:
	int mouseX = 0;
	int mouseY = 0;
	MouseButton button;
};
class MouseReleasedEvent : public Event {
public:
	MouseReleasedEvent(int mouseX, int mouseY, MouseButton button);

	REGISTER_EVENT_TYPE(MouseReleasedEvent)

	std::pair<int, int> getMousePosition() const;
	MouseButton getMouseButton() const;

private:
	int mouseX = 0;
	int mouseY = 0;
	MouseButton button;
};
class MouseMovedEvent : public Event {
public:
	MouseMovedEvent(int mouseX, int mouseY);

	REGISTER_EVENT_TYPE(MouseMovedEvent)

	std::pair<int, int> getMousePosition() const;

private:
	int mouseX = 0;
	int mouseY = 0;
};
class CollisionEvent : public Event {
public:
	CollisionEvent(Collision);

	REGISTER_EVENT_TYPE(CollisionEvent)

	Collision getCollisionData() const;

private:
	Collision collisionData;
};
class TextSubmitEvent : public Event {
public:
	TextSubmitEvent(std::string submittedText);

	REGISTER_EVENT_TYPE(TextSubmitEvent)

	std::string getText() const;

private:
	std::string text;
};
class ShutDownEvent : public Event {
public:
	ShutDownEvent() : Event("ShutDownEvent") {};

	REGISTER_EVENT_TYPE(ShutDownEvent)

private:
};
// class ButtonClickEvent : public Event {
// public:
//     ButtonClickEvent(int x,int y,int width,int height);

//     REGISTER_EVENT_TYPE(TextSubmitEvent)

//     std::string getText() const;

// private:
//     std::string text;
// };
