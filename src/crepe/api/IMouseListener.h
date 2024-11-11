#pragma once
#include "Event.h"
#include "EventHandler.h"
#include "EventManager.h"

class IMouseListener {
public:
	IMouseListener();
    virtual ~IMouseListener();

    virtual bool on_mouse_clicked(const MouseClickEvent & event) = 0;
    virtual bool on_mouse_pressed(const MousePressEvent & event) = 0;
    virtual bool on_mouse_released(const MouseReleaseEvent & event) = 0;
    virtual bool on_mouse_moved(const MouseMoveEvent & event) = 0;

protected:
    void subscribe_events(int listenerId = 0);
    void unsubscribe_events(int listenerId = 0);

private:
    EventHandler<MouseClickEvent> mouse_click_handler;
    EventHandler<MousePressEvent> mouse_press_handler;
    EventHandler<MouseReleaseEvent> mouse_release_handler;
    EventHandler<MouseMoveEvent> mouse_move_handler;
};
