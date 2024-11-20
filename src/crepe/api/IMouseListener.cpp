#include "IMouseListener.h"

using namespace crepe;

IMouseListener::IMouseListener(event_channel_t channel)
	: event_manager(EventManager::get_instance()) {
	this->click_id = event_manager.subscribe<MouseClickEvent>(
		[this](const MouseClickEvent & event) { return this->on_mouse_clicked(event); },
		channel);

	this->press_id = event_manager.subscribe<MousePressEvent>(
		[this](const MousePressEvent & event) { return this->on_mouse_pressed(event); },
		channel);

	this->release_id = event_manager.subscribe<MouseReleaseEvent>(
		[this](const MouseReleaseEvent & event) { return this->on_mouse_released(event); },
		channel);

	this->move_id = event_manager.subscribe<MouseMoveEvent>(
		[this](const MouseMoveEvent & event) { return this->on_mouse_moved(event); }, channel);
}

IMouseListener::~IMouseListener() {
	// Unsubscribe event handlers
	event_manager.unsubscribe(this->click_id);
	event_manager.unsubscribe(this->press_id);
	event_manager.unsubscribe(this->release_id);
	event_manager.unsubscribe(this->move_id);
}
