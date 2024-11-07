#include "iKeyListener.h"

IKeyListener::~IKeyListener() { unsubscribeEvents(); }

void IKeyListener::subscribeEvents(int listenerId) {
	keyPressedHandler
		= [this](const KeyPressedEvent & event) { this->onKeyPressed(event); };
	keyReleasedHandler = [this](const KeyReleasedEvent & event) {
		this->onKeyReleased(event);
	};

	subscribe<KeyPressedEvent>(keyPressedHandler, listenerId);
	subscribe<KeyReleasedEvent>(keyReleasedHandler, listenerId);
}

void IKeyListener::unsubscribeEvents(int listenerId) {
	unsubscribe<KeyPressedEvent>(keyPressedHandler, listenerId);
	unsubscribe<KeyReleasedEvent>(keyReleasedHandler, listenerId);
}
