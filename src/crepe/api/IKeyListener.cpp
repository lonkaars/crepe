#include "IKeyListener.h"

using namespace crepe;

// Constructor with specified channel
IKeyListener::IKeyListener(int channel) :
	  event_manager(EventManager::get_instance()) {
	press_id = event_manager.subscribe<KeyPressEvent>([this](const KeyPressEvent & event) { return this->on_key_pressed(event); }, channel);
	release_id = event_manager.subscribe<KeyReleaseEvent>([this](const KeyReleaseEvent & event) { return this->on_key_released(event); }, channel);
}

// Destructor, unsubscribe events
IKeyListener::~IKeyListener() { 
	event_manager.unsubscribe(press_id);
	event_manager.unsubscribe(release_id);
}

