#pragma once
#include "Event.h"
#include "EventHandler.h"
#include "EventManager.h"
class IKeyListener {
public:
	IKeyListener(int channel);
	IKeyListener();
    virtual ~IKeyListener();
    virtual bool on_key_pressed(const KeyPressEvent & event) = 0;
    virtual bool on_key_released(const KeyReleaseEvent & event) = 0;
	void activate_keys(int listenerId = 0);
    void deactivate_keys();

protected:
    void subscribe_events(int listenerId = 0);
    void unsubscribe_events(int listenerId = 0);
    

private:
	bool active = true;
	int channel = 0;
    EventHandler<KeyPressEvent> key_pressed_handler;
    EventHandler<KeyReleaseEvent> key_released_handler;
};
