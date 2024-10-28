#include "event.h"
#include "eventManager.h"
#include "eventHandler.h"
class IMouseListener {
public:
    virtual ~IMouseListener() {
        unsubscribeEvents();
    }

    virtual void onMouseClicked(const MouseClickEvent& event) = 0;
    virtual void onMousePressed(const MousePressedEvent& event) = 0;
    virtual void onMouseReleased(const MouseReleasedEvent& event) = 0;
    virtual void onMouseMoved(const MouseMovedEvent& event) = 0;

protected:
    void subscribeEvents(int listenerId = 0) {
        mouseClickHandler = [this](const MouseClickEvent& event) { this->onMouseClicked(event); };
        mousePressHandler = [this](const MousePressedEvent& event) { this->onMousePressed(event); };
        mouseReleaseHandler = [this](const MouseReleasedEvent& event) { this->onMouseReleased(event); };
        mouseMoveHandler = [this](const MouseMovedEvent& event) { this->onMouseMoved(event); };

        subscribe<MouseClickEvent>(mouseClickHandler, listenerId);
        subscribe<MousePressedEvent>(mousePressHandler, listenerId);
        subscribe<MouseReleasedEvent>(mouseReleaseHandler, listenerId);
        subscribe<MouseMovedEvent>(mouseMoveHandler, listenerId);
    }

    void unsubscribeEvents(int listenerId = 0) {
        unsubscribe<MouseClickEvent>(mouseClickHandler, listenerId);
        unsubscribe<MousePressedEvent>(mousePressHandler, listenerId);
        unsubscribe<MouseReleasedEvent>(mouseReleaseHandler, listenerId);
        unsubscribe<MouseMovedEvent>(mouseMoveHandler, listenerId);
    }

private:
    EventHandler<MouseClickEvent> mouseClickHandler;
    EventHandler<MousePressedEvent> mousePressHandler;
    EventHandler<MouseReleasedEvent> mouseReleaseHandler;
    EventHandler<MouseMovedEvent> mouseMoveHandler;
};
