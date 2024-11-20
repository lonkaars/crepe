#include "IKeyListener.h"

using namespace crepe;


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
	key_pressed_handler
		= [this](const KeyPressEvent & event) { return this->on_key_pressed(event); };
	key_released_handler
		= [this](const KeyReleaseEvent & event) { return this->on_key_released(event); };

	event_manager.subscribe<KeyPressEvent>(this->key_pressed_handler,
										   this->channel);
	event_manager.subscribe<KeyReleaseEvent>(this->key_released_handler,
											 this->channel);
}

// Unsubscribe from key events
void IKeyListener::unsubscribe_events() {
	event_manager.unsubscribe<KeyPressEvent>(this->key_pressed_handler, this->channel);
	event_manager.unsubscribe<KeyReleaseEvent>(this->key_released_handler, this->channel);
}

