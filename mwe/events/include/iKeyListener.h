#pragma once
#include "event.h"
#include "eventManager.h"
#include "eventHandler.h"
class IKeyListener {
public:
    virtual ~IKeyListener();
    virtual void onKeyPressed(const KeyPressedEvent& event) = 0;
    virtual void onKeyReleased(const KeyReleasedEvent& event) = 0;

protected:
    void subscribeEvents(int listenerId = 0);
    void unsubscribeEvents(int listenerId = 0);

private:
    EventHandler<KeyPressedEvent> keyPressedHandler;
    EventHandler<KeyReleasedEvent> keyReleasedHandler;
};

