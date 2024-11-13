#include "IMouseListener.h"
IMouseListener::IMouseListener(int channel){
	this->channel = channel;
}
IMouseListener::IMouseListener(){
	this->subscribe_events();
}
IMouseListener::~IMouseListener() {
    this->unsubscribe_events();
}

void IMouseListener::subscribe_events() {
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
    EventManager::get_instance().subscribe<MouseClickEvent>(std::move(this->mouse_click_handler), this->channel);
    EventManager::get_instance().subscribe<MousePressEvent>(std::move(this->mouse_press_handler), this->channel);
    EventManager::get_instance().subscribe<MouseReleaseEvent>(std::move(this->mouse_release_handler), this->channel);
    EventManager::get_instance().subscribe<MouseMoveEvent>(std::move(this->mouse_move_handler), this->channel);
}

void IMouseListener::unsubscribe_events() {
    EventManager::get_instance().unsubscribe<MouseClickEvent>(this->mouse_click_handler, this->channel);
    EventManager::get_instance().unsubscribe<MousePressEvent>(this->mouse_press_handler, this->channel);
    EventManager::get_instance().unsubscribe<MouseReleaseEvent>(this->mouse_release_handler, this->channel);
    EventManager::get_instance().unsubscribe<MouseMoveEvent>(this->mouse_move_handler, this->channel);
}
void IMouseListener::activate_keys() { 
	if(this->active){
		return;
	}
	this->subscribe_events(); 
}
void IMouseListener::deactivate_keys() { 
	if(!this->active){
		return;
	}
	this->unsubscribe_events(); 
}
void IMouseListener::set_channel(int channel){
	this->channel = channel;
}
