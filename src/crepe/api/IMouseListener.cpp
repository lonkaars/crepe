#include "IMouseListener.h"

using namespace crepe;

IMouseListener::IMouseListener(int channel)
	: event_manager(EventManager::get_instance()),
	  channel(channel) {
	this->subscribe_events();
}

IMouseListener::~IMouseListener() { this->unsubscribe_events(); }

void IMouseListener::subscribe_events() {
	// Define handler lambdas and subscribe them
	mouse_click_handler
		= [this](const MouseClickEvent & event) { return this->on_mouse_clicked(event); };
	mouse_press_handler
		= [this](const MousePressEvent & event) { return this->on_mouse_pressed(event); };
	mouse_release_handler
		= [this](const MouseReleaseEvent & event) { return this->on_mouse_released(event); };
	mouse_move_handler
		= [this](const MouseMoveEvent & event) { return this->on_mouse_moved(event); };

	// Subscribe event handlers (no need for std::move)
	event_manager.subscribe<MouseClickEvent>(mouse_click_handler, this->channel);
	event_manager.subscribe<MousePressEvent>(mouse_press_handler, this->channel);
	event_manager.subscribe<MouseReleaseEvent>(mouse_release_handler,
											   this->channel);
	event_manager.subscribe<MouseMoveEvent>(mouse_move_handler, this->channel);
}

void IMouseListener::unsubscribe_events() {
	// Unsubscribe event handlers
	event_manager.unsubscribe<MouseClickEvent>(mouse_click_handler, this->channel);
	event_manager.unsubscribe<MousePressEvent>(mouse_press_handler, this->channel);
	event_manager.unsubscribe<MouseReleaseEvent>(mouse_release_handler, this->channel);
	event_manager.unsubscribe<MouseMoveEvent>(mouse_move_handler, this->channel);
}
