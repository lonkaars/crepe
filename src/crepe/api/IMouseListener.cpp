#include "IMouseListener.h"
IMouseListener::IMouseListener(){
	subscribe_events();
}
IMouseListener::~IMouseListener() {
    unsubscribe_events();
}

void IMouseListener::subscribe_events(int listenerId) {
    // Define handler lambdas and subscribe them
    mouse_click_handler = [this](const MouseClickEvent& event) {
        return this->on_mouse_clicked(event);
    };
    mouse_press_handler = [this](const MousePressEvent& event) {
        return this->on_mouse_pressed(event);
    };
    mouse_release_handler = [this](const MouseReleaseEvent& event) {
        return this->on_mouse_released(event);
    };
    mouse_move_handler = [this](const MouseMoveEvent& event) {
        return this->on_mouse_moved(event);
    };
    EventManager::get_instance().subscribe<MouseClickEvent>(std::move(mouse_click_handler), listenerId);
    EventManager::get_instance().subscribe<MousePressEvent>(std::move(mouse_press_handler), listenerId);
    EventManager::get_instance().subscribe<MouseReleaseEvent>(std::move(mouse_release_handler), listenerId);
    EventManager::get_instance().subscribe<MouseMoveEvent>(std::move(mouse_move_handler), listenerId);
}

void IMouseListener::unsubscribe_events(int listenerId) {
    EventManager::get_instance().unsubscribe<MouseClickEvent>(mouse_click_handler, listenerId);
    EventManager::get_instance().unsubscribe<MousePressEvent>(mouse_press_handler, listenerId);
    EventManager::get_instance().unsubscribe<MouseReleaseEvent>(mouse_release_handler, listenerId);
    EventManager::get_instance().unsubscribe<MouseMoveEvent>(mouse_move_handler, listenerId);
}
