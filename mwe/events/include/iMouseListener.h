#pragma once
#include "event.h"
#include "eventHandler.h"
#include "eventManager.h"

class IMouseListener {
public:
    virtual ~IMouseListener();

    virtual void onMouseClicked(const MouseClickEvent& event) = 0;
    virtual void onMousePressed(const MousePressedEvent& event) = 0;
    virtual void onMouseReleased(const MouseReleasedEvent& event) = 0;
    virtual void onMouseMoved(const MouseMovedEvent& event) = 0;
protected:
    void subscribeEvents(int listenerId = 0);
    void unsubscribeEvents(int listenerId = 0);

private:
    EventHandler<MouseClickEvent> mouseClickHandler;
    EventHandler<MousePressedEvent> mousePressHandler;
    EventHandler<MouseReleasedEvent> mouseReleaseHandler;
    EventHandler<MouseMovedEvent> mouseMoveHandler;
};
