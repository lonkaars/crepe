#include "IKeyListener.h"

using namespace crepe;

// Constructor with default channel
IKeyListener::IKeyListener()
	: channel(0),
	  active(true),
	  event_manager(EventManager::get_instance()) {
	this->subscribe_events();
}

// Constructor with specified channel
IKeyListener::IKeyListener(int channel)
	: channel(channel),
	  active(true),
	  event_manager(EventManager::get_instance()) {
	this->subscribe_events();
}

// Destructor, unsubscribe events
IKeyListener::~IKeyListener() { this->unsubscribe_events(); }

// Subscribe to key events
void IKeyListener::subscribe_events() {
	key_pressed_handler = [this](const KeyPressEvent & event) {
		return this->on_key_pressed(event);
	};
	key_released_handler = [this](const KeyReleaseEvent & event) {
		return this->on_key_released(event);
	};

	event_manager.subscribe<KeyPressEvent>(std::move(this->key_pressed_handler),
										   this->channel);
	event_manager.subscribe<KeyReleaseEvent>(
		std::move(this->key_released_handler), this->channel);
}

// Unsubscribe from key events
void IKeyListener::unsubscribe_events() {
	event_manager.unsubscribe<KeyPressEvent>(this->key_pressed_handler,
											 this->channel);
	event_manager.unsubscribe<KeyReleaseEvent>(this->key_released_handler,
											   this->channel);
}

// Activate key listening
void IKeyListener::activate_keys() {
	if (this->active) {
		return;
	}
	this->active = true;
	this->subscribe_events();
}

// Deactivate key listening
void IKeyListener::deactivate_keys() {
	if (!this->active) {
		return;
	}
	this->active = false;
	this->unsubscribe_events();
}

// Set a new channel for key events
void IKeyListener::set_channel(int channel) {
	this->unsubscribe_events();
	this->channel = channel;
	this->subscribe_events();
}
