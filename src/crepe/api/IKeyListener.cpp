#include "IKeyListener.h"
#include <iostream>
IKeyListener::IKeyListener(){
	this->channel = channel;
	subscribe_events();
}
IKeyListener::IKeyListener(int channel){
	this->channel = channel;
	subscribe_events(channel);
}
IKeyListener::~IKeyListener() { 
	unsubscribe_events(); 
}

void IKeyListener::subscribe_events(int listenerId) {
    key_pressed_handler = [this](const KeyPressEvent & event) {
        return this->on_key_pressed(event);
    };
    key_released_handler = [this](const KeyReleaseEvent & event) {
        return this->on_key_released(event);
    };
    EventManager::get_instance().subscribe<KeyPressEvent>(std::move(key_pressed_handler), listenerId);
    EventManager::get_instance().subscribe<KeyReleaseEvent>(std::move(key_released_handler), listenerId);
}

void IKeyListener::unsubscribe_events(int listenerId) {
    EventManager::get_instance().unsubscribe<KeyPressEvent>(key_pressed_handler , listenerId);
    EventManager::get_instance().unsubscribe<KeyReleaseEvent>(key_released_handler , listenerId);
	std::cout << std::endl;
}
void IKeyListener::activate_keys(int listenerId) { 
	if(this->active){
		return;
	}
	subscribe_events(listenerId); 
}
void IKeyListener::deactivate_keys() { 
	if(!this->active){
		return;
	}
	unsubscribe_events(); 
}
