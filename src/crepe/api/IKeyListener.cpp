#include "IKeyListener.h"

using namespace crepe;

IKeyListener::IKeyListener() {
	this->channel = channel;
	this->subscribe_events();
}
IKeyListener::IKeyListener(int channel) {
	this->channel = channel;
	this->subscribe_events();
}
IKeyListener::~IKeyListener() { this->unsubscribe_events(); }

void IKeyListener::subscribe_events() {
	key_pressed_handler = [this](const KeyPressEvent & event) {
		return this->on_key_pressed(event);
	};
	key_released_handler = [this](const KeyReleaseEvent & event) {
		return this->on_key_released(event);
	};
	EventManager::get_instance().subscribe<KeyPressEvent>(
		std::move(this->key_pressed_handler), this->channel);
	EventManager::get_instance().subscribe<KeyReleaseEvent>(
		std::move(this->key_released_handler), this->channel);
}

void IKeyListener::unsubscribe_events() {
	EventManager::get_instance().unsubscribe<KeyPressEvent>(
		this->key_pressed_handler, channel);
	EventManager::get_instance().unsubscribe<KeyReleaseEvent>(
		this->key_released_handler, channel);
	std::cout << std::endl;
}
void IKeyListener::activate_keys() {
	if (this->active) {
		return;
	}
	this->subscribe_events();
}
void IKeyListener::deactivate_keys() {
	if (!this->active) {
		return;
	}
	this->unsubscribe_events();
}
void IKeyListener::set_channel(int channel) {
	this->unsubscribe_events();
	this->channel = channel;
	this->subscribe_events();
}
