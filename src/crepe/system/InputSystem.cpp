
#include "../api/Button.h"
#include "../manager/ComponentManager.h"
#include "../manager/EventManager.h"

#include "InputSystem.h"

using namespace crepe;

void InputSystem::update() {
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

	ivec2 camera_origin;
	camera_origin.y = cam_transform.position.y + current_cam.data.postion_offset.y
					  - (current_cam.viewport_size.y / 2);
	camera_origin.x = cam_transform.position.x + current_cam.data.postion_offset.x
					  - (current_cam.viewport_size.x / 2);

	for (const SDLContext::EventData & event : event_list) {
		// Only calculate mouse coordinates for relevant events
		if (event.event_type == SDLContext::EventType::MOUSEDOWN
			|| event.event_type == SDLContext::EventType::MOUSEUP
			|| event.event_type == SDLContext::EventType::MOUSEMOVE
			|| event.event_type == SDLContext::EventType::MOUSEWHEEL) {

			int adjusted_mouse_x = event.mouse_data.mouse_position.x + camera_origin.x;
			int adjusted_mouse_y = event.mouse_data.mouse_position.y + camera_origin.y;

			// Check if the mouse is within the viewport
			bool mouse_in_viewport
				= !(adjusted_mouse_x < camera_origin.x
					|| adjusted_mouse_x > camera_origin.x + current_cam.viewport_size.x
					|| adjusted_mouse_y < camera_origin.y
					|| adjusted_mouse_y > camera_origin.y + current_cam.viewport_size.y);

			if (!mouse_in_viewport) continue;

			// Handle mouse-specific events
			switch (event.event_type) {
				case SDLContext::EventType::MOUSEDOWN:
					event_mgr.queue_event<MousePressEvent>({
						.mouse_pos = {adjusted_mouse_x, adjusted_mouse_y},
						.button = event.mouse_data.mouse_button,
					});
					this->last_mouse_down_position = {adjusted_mouse_x, adjusted_mouse_y};
					this->last_mouse_button = event.mouse_data.mouse_button;
					break;

				case SDLContext::EventType::MOUSEUP: {
					event_mgr.queue_event<MouseReleaseEvent>({
						.mouse_pos = {adjusted_mouse_x, adjusted_mouse_y},
						.button = event.mouse_data.mouse_button,
					});
					int delta_x = adjusted_mouse_x - this->last_mouse_down_position.x;
					int delta_y = adjusted_mouse_y - this->last_mouse_down_position.y;

					if (this->last_mouse_button == event.mouse_data.mouse_button
						&& std::abs(delta_x) <= click_tolerance
						&& std::abs(delta_y) <= click_tolerance) {
						event_mgr.queue_event<MouseClickEvent>({
							.mouse_pos = {adjusted_mouse_x, adjusted_mouse_y},
							.button = event.mouse_data.mouse_button,
						});
						this->handle_click(event.mouse_data.mouse_button, adjusted_mouse_x,
										   adjusted_mouse_y);
					}
					break;
				}

				case SDLContext::EventType::MOUSEMOVE:
					event_mgr.queue_event<MouseMoveEvent>({
						.mouse_pos = {adjusted_mouse_x, adjusted_mouse_y},
						.mouse_delta = event.mouse_data.rel_mouse_move,
					});
					this->handle_move(event, adjusted_mouse_x, adjusted_mouse_y);
					break;

				case SDLContext::EventType::MOUSEWHEEL:
					event_mgr.queue_event<MouseScrollEvent>({
						.mouse_pos = {adjusted_mouse_x, adjusted_mouse_y},
						.scroll_direction = event.mouse_data.scroll_direction,
						.scroll_delta = event.mouse_data.scroll_delta,
					});
					break;

				default:
					break;
			}
		} else {
			// Handle non-mouse events
			switch (event.event_type) {
				case SDLContext::EventType::KEYDOWN:
					event_mgr.queue_event<KeyPressEvent>(
						{.repeat = event.key_data.key_repeat, .key = event.key_data.key});
					break;
				case SDLContext::EventType::KEYUP:
					event_mgr.queue_event<KeyReleaseEvent>({.key = event.key_data.key});
					break;
				case SDLContext::EventType::SHUTDOWN:
					event_mgr.queue_event<ShutDownEvent>({});
					break;
				case SDLContext::EventType::WINDOW_EXPOSE:
					event_mgr.queue_event<WindowExposeEvent>({});
					break;
				case SDLContext::EventType::WINDOW_RESIZE:
					event_mgr.queue_event<WindowResizeEvent>(
						WindowResizeEvent{.dimensions = event.window_data.resize_dimension});
					break;
				case SDLContext::EventType::WINDOW_MOVE:
					event_mgr.queue_event<WindowMoveEvent>(
						{.delta_move = event.window_data.move_delta});
					break;
				case SDLContext::EventType::WINDOW_MINIMIZE:
					event_mgr.queue_event<WindowMinimizeEvent>({});
					break;
				case SDLContext::EventType::WINDOW_MAXIMIZE:
					event_mgr.queue_event<WindowMaximizeEvent>({});
					break;
				case SDLContext::EventType::WINDOW_FOCUS_GAIN:
					event_mgr.queue_event<WindowFocusGainEvent>({});
					break;
				case SDLContext::EventType::WINDOW_FOCUS_LOST:
					event_mgr.queue_event<WindowFocusLostEvent>({});
					break;
				default:
					break;
			}
		}
	}
}

void InputSystem::handle_move(const SDLContext::EventData & event_data,
							  const int adjusted_mouse_x, const int adjusted_mouse_y) {
	ComponentManager & mgr = this->mediator.component_manager;

	RefVector<Button> buttons = mgr.get_components_by_type<Button>();

	for (Button & button : buttons) {
		RefVector<Transform> transform_vec
			= mgr.get_components_by_id<Transform>(button.game_object_id);
		Transform & transform(transform_vec.front().get());

		bool was_hovering = button.hover;
		if (button.active
			&& this->is_mouse_inside_button(adjusted_mouse_x, adjusted_mouse_y, button,
											transform)) {
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

void InputSystem::handle_click(const MouseButton & mouse_button, const int adjusted_mouse_x,
							   const int adjusted_mouse_y) {
	ComponentManager & mgr = this->mediator.component_manager;

	RefVector<Button> buttons = mgr.get_components_by_type<Button>();

	for (Button & button : buttons) {
		RefVector<Transform> transform_vec
			= mgr.get_components_by_id<Transform>(button.game_object_id);
		Transform & transform = transform_vec.front().get();

		if (button.active
			&& this->is_mouse_inside_button(adjusted_mouse_x, adjusted_mouse_y, button,
											transform)) {
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
