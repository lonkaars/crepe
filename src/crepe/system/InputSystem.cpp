#include "api/Button.h"
#include "api/EventManager.h"
#include "ComponentManager.h"

#include "InputSystem.h"

using namespace crepe;

void InputSystem::update() {
	EventManager & event_mgr = EventManager::get_instance();
	std::vector<SDLContext::EventData> event_list = SDLContext::get_instance().get_events();

	for (const SDLContext::EventData & event : event_list) {
		switch (event.event_type) {
			case SDLContext::EventType::KEYDOWN: {
				event_mgr.queue_event<KeyPressEvent>(KeyPressEvent{
					.repeat = event.key_repeat,
					.key = event.key,
				});
				break;
			}
			case SDLContext::EventType::KEYUP: {
				event_mgr.queue_event<KeyReleaseEvent>(KeyReleaseEvent{
					.key = event.key,
				});
				break;
			}
			case SDLContext::EventType::MOUSEDOWN: {
				event_mgr.queue_event<MousePressEvent>(MousePressEvent{
					.mouse_x = event.mouse_position.first,
					.mouse_y = event.mouse_position.second,
					.button = event.mouse_button,
				});
				last_mouse_down_position = event.mouse_position;
				last_mouse_button = event.mouse_button;
				break;
			}
			case SDLContext::EventType::MOUSEUP: {
				event_mgr.queue_event<MouseReleaseEvent>(MouseReleaseEvent{
					.mouse_x = event.mouse_position.first,
					.mouse_y = event.mouse_position.second,
					.button = event.mouse_button,
				});

				int delta_x = event.mouse_position.first - last_mouse_down_position.first;
				int delta_y = event.mouse_position.second - last_mouse_down_position.second;
		
				if (last_mouse_button == event.mouse_button
					&& std::abs(delta_x) <= click_tolerance
					&& std::abs(delta_y) <= click_tolerance) {
					event_mgr.queue_event<MouseClickEvent>(MouseClickEvent{
						.mouse_x = event.mouse_position.first,
						.mouse_y = event.mouse_position.second,
						.button = event.mouse_button,
					});

					handle_click(event);
				}
				break;
			}
			case SDLContext::EventType::MOUSEMOVE: {
				event_mgr.queue_event<MouseMoveEvent>(MouseMoveEvent{
					.mouse_x = event.mouse_position.first,
					.mouse_y = event.mouse_position.second,
					.rel_x = event.rel_mouse_move.first,
					.rel_y = event.rel_mouse_move.second,
				});
				handle_move(event);
				break;
			}
			case SDLContext::EventType::MOUSEWHEEL: {
				event_mgr.queue_event<MouseScrollEvent>(MouseScrollEvent{
					.scroll_x = event.wheel_delta,
					.scroll_y = 0,
					.direction = event.wheel_delta,
				});
				break;
			}
			case SDLContext::EventType::SHUTDOWN: {
				event_mgr.queue_event<ShutDownEvent>(ShutDownEvent{});
				break;
			}
			default:
				break;
		}
	}
}

void InputSystem::handle_move(const SDLContext::EventData & event_data) {
	ComponentManager & mgr = this->component_manager;

	RefVector<Button> buttons = mgr.get_components_by_type<Button>();
	RefVector<Transform> transforms = mgr.get_components_by_type<Transform>();

	for (Button & button : buttons) {
		OptionalRef<Transform> transform = find_transform_for_button(button, transforms);
		if (!transform) continue;

		if (button.active && is_mouse_inside_button(event_data, button, transform)) {
			button.hover = true;
		} else {
			button.hover = false;
		}
	}
}

void InputSystem::handle_click(const SDLContext::EventData & event_data) {
	ComponentManager & mgr = this->component_manager;

	RefVector<Button> buttons = mgr.get_components_by_type<Button>();
	RefVector<Transform> transforms = mgr.get_components_by_type<Transform>();

	for (Button & button : buttons) {
		OptionalRef<Transform> transform_ref = find_transform_for_button(button, transforms);

		if (button.active && is_mouse_inside_button(event_data, button, transform_ref)) {
			handle_button_press(button);
		}
	}
}


OptionalRef<Transform> InputSystem::find_transform_for_button(
    Button & button, RefVector<Transform>& transforms) {
    
    for (auto& transform : transforms) {
        if (button.game_object_id == transform.get().game_object_id) {
            return OptionalRef<Transform>(transform);
        }
    }

    return OptionalRef<Transform>();
}


bool InputSystem::is_mouse_inside_button(const SDLContext::EventData & event_data,
										 const Button & button, const Transform & transform) {
	return event_data.mouse_position.first >= transform.position.x
		   && event_data.mouse_position.first <= transform.position.x + button.width
		   && event_data.mouse_position.second >= transform.position.y
		   && event_data.mouse_position.second <= transform.position.y + button.height;
}

void InputSystem::handle_button_press(Button & button) {
	if (button.is_toggle) {
		if (!button.is_pressed && button.on_click) {
			button.on_click();
		}
		button.is_pressed = !button.is_pressed;
	} else if (button.on_click) {
		button.on_click();
	}
}
