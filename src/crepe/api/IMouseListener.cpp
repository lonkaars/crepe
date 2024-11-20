#include "IMouseListener.h"

using namespace crepe;

IMouseListener::IMouseListener(int channel)
	: event_manager(EventManager::get_instance()) {
	click_id =  event_manager.subscribe<MouseClickEvent>(
		[this](const MouseClickEvent & event) { return this->on_mouse_clicked(event); },
		channel);

	press_id = event_manager.subscribe<MousePressEvent>(
		[this](const MousePressEvent & event) { return this->on_mouse_pressed(event); },
		channel);

	release_id = event_manager.subscribe<MouseReleaseEvent>(
		[this](const MouseReleaseEvent & event) { return this->on_mouse_released(event); },
		channel);

	move_id = event_manager.subscribe<MouseMoveEvent>(
		[this](const MouseMoveEvent & event) { return this->on_mouse_moved(event); },
		channel);
}

IMouseListener::~IMouseListener() {
	 // Unsubscribe event handlers
	event_manager.unsubscribe(click_id);
	event_manager.unsubscribe(press_id);
	event_manager.unsubscribe(release_id);
	event_manager.unsubscribe(move_id);
	}
