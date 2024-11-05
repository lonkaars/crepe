#pragma once
#include "event.h"
#include "eventHandler.h"
#include "eventManager.h"
class IKeyListener {
public:
	virtual ~IKeyListener();
	virtual void onKeyPressed(const KeyPressedEvent & event) = 0;
	virtual void onKeyReleased(const KeyReleasedEvent & event) = 0;

protected:
	void subscribeEvents(int listenerId = 0);
	void unsubscribeEvents(int listenerId = 0);
	void activate(int listenerId = 0) { subscribeEvents(listenerId); }
	void deactivate(int listenerId = 0) { unsubscribeEvents(listenerId); }

private:
	EventHandler<KeyPressedEvent> keyPressedHandler;
	EventHandler<KeyReleasedEvent> keyReleasedHandler;
};
