#include "IKeyListener.h"
#include <iostream>
IKeyListener::IKeyListener(){
	
	subscribe_events(0);
}
IKeyListener::~IKeyListener() { 
	std::cout << "destructor call" << std::endl;
	unsubscribe_events(); 
	}

void IKeyListener::subscribe_events(int listenerId) {
    auto key_pressed_handler = [this](const KeyPressEvent & event) {
        return this->on_key_pressed(event);
    };
    auto key_released_handler = [this](const KeyReleaseEvent & event) {
        return this->on_key_released(event);
    };
	std::cout << "IKeyListener subscribe: " << std::endl;
    EventManager::get_instance().subscribe<KeyPressEvent>(key_pressed_handler, listenerId);
    EventManager::get_instance().subscribe<KeyReleaseEvent>(key_released_handler, listenerId);
	std::cout << std::endl;
}

void IKeyListener::unsubscribe_events(int listenerId) {
	std::cout << "IKeyListener unsubscribe: " << std::endl;
	std::cout << "key_pressed_handler name: " << key_pressed_handler.target_type().name() << std::endl;
	std::cout << "key_released_handler name: " << key_released_handler.target_type().name()  << std::endl;
    EventManager::get_instance().unsubscribe<KeyPressEvent>(key_pressed_handler , listenerId);
    EventManager::get_instance().unsubscribe<KeyReleaseEvent>(key_released_handler , listenerId);
	std::cout << std::endl;
}
