#pragma once
#include "Event.h"
#include "EventHandler.h"
#include "EventManager.h"
class IKeyListener {
public:
    virtual ~IKeyListener();
    virtual bool on_key_pressed(const KeyPressEvent & event) = 0;
    virtual bool on_key_released(const KeyReleaseEvent & event) = 0;

protected:
    void subscribe_events(int listenerId = 0);
    void unsubscribe_events(int listenerId = 0);
    void activate(int listenerId = 0) { subscribe_events(listenerId); }
    void deactivate(int listenerId = 0) { unsubscribe_events(listenerId); }

private:
    EventHandler<KeyPressEvent> key_pressed_handler;
    EventHandler<KeyReleaseEvent> key_released_handler;
};
