#include "IKeyListener.h"

IKeyListener::~IKeyListener() { unsubscribe_events(); }

void IKeyListener::subscribe_events(int listenerId) {
    auto key_pressed_handler = [this](const KeyPressEvent & event) {
        return this->on_key_pressed(event);
    };
    auto key_released_handler = [this](const KeyReleaseEvent & event) {
        return this->on_key_released(event);
    };

    EventManager::get_instance().subscribe<KeyPressEvent>(std::move(key_pressed_handler), listenerId);
    EventManager::get_instance().subscribe<KeyReleaseEvent>(std::move(key_released_handler), listenerId);
}

void IKeyListener::unsubscribe_events(int listenerId) {
    EventManager::get_instance().unsubscribe(std::type_index(typeid(KeyPressEvent)), "on_key_pressed", listenerId);
    EventManager::get_instance().unsubscribe(std::type_index(typeid(KeyReleaseEvent)), "on_key_released", listenerId);
}
