#include "../api/Button.h"
#include "../manager/ComponentManager.h"
#include "../manager/EventManager.h"

#include "InputSystem.h"

using namespace crepe;

void InputSystem::fixed_update() {
	ComponentManager & mgr = this->mediator.component_manager;
	EventManager & event_mgr = this->mediator.event_manager;
	std::vector<SDLContext::EventData> event_list = SDLContext::get_instance().get_events();
	RefVector<Button> buttons = mgr.get_components_by_type<Button>();
	RefVector<Camera> cameras = mgr.get_components_by_type<Camera>();
	OptionalRef<Camera> curr_cam_ref;
	// Find the active camera
	for (Camera & cam : cameras) {
		if (!cam.active) continue;
		curr_cam_ref = cam;
		break;
	}
	if (!curr_cam_ref) return;
	Camera & current_cam = curr_cam_ref;
	RefVector<Transform> transform_vec
		= mgr.get_components_by_id<Transform>(current_cam.game_object_id);
	Transform & cam_transform = transform_vec.front().get();
	int camera_origin_x = cam_transform.position.x + current_cam.data.postion_offset.x
						  - (current_cam.viewport_size.x / 2);
	int camera_origin_y = cam_transform.position.y + current_cam.data.postion_offset.y
						  - (current_cam.viewport_size.y / 2);

	for (const SDLContext::EventData & event : event_list) {
		int world_mouse_x = event.mouse_position.x + camera_origin_x;
		int world_mouse_y = event.mouse_position.y + camera_origin_y;
		// check if the mouse is within the viewport
		bool mouse_in_viewport
			= !(world_mouse_x < camera_origin_x
				|| world_mouse_x > camera_origin_x + current_cam.viewport_size.x
				|| world_mouse_y < camera_origin_y
				|| world_mouse_y > camera_origin_y + current_cam.viewport_size.y);

		switch (event.event_type) {
			case SDLContext::EventType::KEYDOWN:
				event_mgr.queue_event<KeyPressEvent>(KeyPressEvent{
					.repeat = event.key_repeat,
					.key = event.key,
				});
				break;
			case SDLContext::EventType::KEYUP:
				event_mgr.queue_event<KeyReleaseEvent>(KeyReleaseEvent{
					.key = event.key,
				});
				break;
			case SDLContext::EventType::MOUSEDOWN:
				if (!mouse_in_viewport) {
					break;
				}
				event_mgr.queue_event<MousePressEvent>(MousePressEvent{
					.mouse_x = world_mouse_x,
					.mouse_y = world_mouse_y,
					.button = event.mouse_button,
				});
				this->last_mouse_down_position = {world_mouse_x, world_mouse_y};
				this->last_mouse_button = event.mouse_button;
				break;
			case SDLContext::EventType::MOUSEUP: {
				if (!mouse_in_viewport) {
					break;
				}
				event_mgr.queue_event<MouseReleaseEvent>(MouseReleaseEvent{
					.mouse_x = world_mouse_x,
					.mouse_y = world_mouse_y,
					.button = event.mouse_button,
				});
				//check if its a click by checking the last button down
				int delta_x = world_mouse_x - this->last_mouse_down_position.x;
				int delta_y = world_mouse_y - this->last_mouse_down_position.y;

				if (this->last_mouse_button == event.mouse_button
					&& std::abs(delta_x) <= click_tolerance
					&& std::abs(delta_y) <= click_tolerance) {
					event_mgr.queue_event<MouseClickEvent>(MouseClickEvent{
						.mouse_x = world_mouse_x,
						.mouse_y = world_mouse_y,
						.button = event.mouse_button,
					});

					this->handle_click(event.mouse_button, world_mouse_x, world_mouse_y);
				}
			} break;
			case SDLContext::EventType::MOUSEMOVE:
				if (!mouse_in_viewport) {
					break;
				}
				event_mgr.queue_event<MouseMoveEvent>(MouseMoveEvent{
					.mouse_x = world_mouse_x,
					.mouse_y = world_mouse_y,
					.delta_x = event.rel_mouse_move.x,
					.delta_y = event.rel_mouse_move.y,
				});
				this->handle_move(event, world_mouse_x, world_mouse_y);
				break;
			case SDLContext::EventType::MOUSEWHEEL:
				event_mgr.queue_event<MouseScrollEvent>(MouseScrollEvent{
					.mouse_x = world_mouse_x,
					.mouse_y = world_mouse_y,
					.scroll_direction = event.scroll_direction,
					.scroll_delta = event.scroll_delta,
				});
				break;
			case SDLContext::EventType::SHUTDOWN:
				event_mgr.queue_event<ShutDownEvent>(ShutDownEvent{});
				break;
			default:
				break;
		}
	}
}
void InputSystem::handle_move(const SDLContext::EventData & event_data,
							  const int world_mouse_x, const int world_mouse_y) {
	ComponentManager & mgr = this->mediator.component_manager;

	RefVector<Button> buttons = mgr.get_components_by_type<Button>();

	for (Button & button : buttons) {
		RefVector<Transform> transform_vec
			= mgr.get_components_by_id<Transform>(button.game_object_id);
		Transform & transform(transform_vec.front().get());

		bool was_hovering = button.hover;
		if (button.active
			&& this->is_mouse_inside_button(world_mouse_x, world_mouse_y, button, transform)) {
			button.hover = true;
			if (!was_hovering && button.on_mouse_enter) {
				button.on_mouse_enter();
			}
		} else {
			button.hover = false;
			// Trigger the on_exit callback if the hover state just changed to false
			if (was_hovering && button.on_mouse_exit) {
				button.on_mouse_exit();
			}
		}
	}
}

void InputSystem::handle_click(const MouseButton & mouse_button, const int world_mouse_x,
							   const int world_mouse_y) {
	ComponentManager & mgr = this->mediator.component_manager;

	RefVector<Button> buttons = mgr.get_components_by_type<Button>();

	for (Button & button : buttons) {
		RefVector<Transform> transform_vec
			= mgr.get_components_by_id<Transform>(button.game_object_id);
		Transform & transform = transform_vec.front().get();

		if (button.active
			&& this->is_mouse_inside_button(world_mouse_x, world_mouse_y, button, transform)) {
			this->handle_button_press(button);
		}
	}
}

bool InputSystem::is_mouse_inside_button(const int mouse_x, const int mouse_y,
										 const Button & button, const Transform & transform) {
	int actual_x = transform.position.x + button.offset.x;
	int actual_y = transform.position.y + button.offset.y;

	int half_width = button.dimensions.x / 2;
	int half_height = button.dimensions.y / 2;

	// Check if the mouse is within the button's boundaries
	return mouse_x >= actual_x - half_width && mouse_x <= actual_x + half_width
		   && mouse_y >= actual_y - half_height && mouse_y <= actual_y + half_height;
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
