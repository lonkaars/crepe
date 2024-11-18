#include "iMouseListener.h"
IMouseListener::~IMouseListener() { unsubscribeEvents(); }

void IMouseListener::subscribeEvents(int listenerId) {
	mouseClickHandler = [this](const MouseClickEvent & event) { this->onMouseClicked(event); };
	mousePressHandler
		= [this](const MousePressedEvent & event) { this->onMousePressed(event); };
	mouseReleaseHandler
		= [this](const MouseReleasedEvent & event) { this->onMouseReleased(event); };
	mouseMoveHandler = [this](const MouseMovedEvent & event) { this->onMouseMoved(event); };

	subscribe<MouseClickEvent>(mouseClickHandler, listenerId);
	subscribe<MousePressedEvent>(mousePressHandler, listenerId);
	subscribe<MouseReleasedEvent>(mouseReleaseHandler, listenerId);
	subscribe<MouseMovedEvent>(mouseMoveHandler, listenerId);
}

void IMouseListener::unsubscribeEvents(int listenerId) {
	unsubscribe<MouseClickEvent>(mouseClickHandler, listenerId);
	unsubscribe<MousePressedEvent>(mousePressHandler, listenerId);
	unsubscribe<MouseReleasedEvent>(mouseReleaseHandler, listenerId);
	unsubscribe<MouseMovedEvent>(mouseMoveHandler, listenerId);
}
