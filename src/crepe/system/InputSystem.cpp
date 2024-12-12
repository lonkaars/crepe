#include <iostream>
#include "../api/Button.h"
#include "../manager/ComponentManager.h"
#include "../manager/EventManager.h"
#include "facade/SDLContext.h"
#include "util/Log.h"

#include "InputSystem.h"

using namespace crepe;

void InputSystem::update() {
	ComponentManager & mgr = this->mediator.component_manager;
	EventManager & event_mgr = this->mediator.event_manager;
	SDLContext & context = this->mediator.sdl_context;
	std::vector<SDLContext::EventData> event_list = context.get_events();
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
	int camera_origin_x = cam_transform.position.x + current_cam.data.postion_offset.x
						  - (current_cam.viewport_size.x / 2);
	int camera_origin_y = cam_transform.position.y + current_cam.data.postion_offset.y
						  - (current_cam.viewport_size.y / 2);

	for (const SDLContext::EventData & event : event_list) {
		// Only calculate mouse coordinates for relevant events
		if (event.event_type == SDLContext::EventType::MOUSEDOWN
			|| event.event_type == SDLContext::EventType::MOUSEUP
			|| event.event_type == SDLContext::EventType::MOUSEMOVE
			|| event.event_type == SDLContext::EventType::MOUSEWHEEL) {

			ivec2 adjusted_mouse;
			std::cout << "mousePos X: " << event.data.mouse_data.mouse_position.x << std::endl;
			std::cout << "mousePos Y: " << event.data.mouse_data.mouse_position.y << std::endl;
			int world_mouse_x = event.data.mouse_data.mouse_position.x + camera_origin_x;
			int world_mouse_y = event.data.mouse_data.mouse_position.y + camera_origin_y;
			// Check if the mouse is within the viewport
			bool mouse_in_viewport
			= !(world_mouse_x < camera_origin_x
				|| world_mouse_x > camera_origin_x + current_cam.viewport_size.x
				|| world_mouse_y < camera_origin_y
				|| world_mouse_y > camera_origin_y + current_cam.viewport_size.y);
			std::cout << "in view " << mouse_in_viewport << std::endl;
			if (!mouse_in_viewport) continue;

			// Handle mouse-specific events
			switch (event.event_type) {
				case SDLContext::EventType::MOUSEDOWN:
					event_mgr.queue_event<MousePressEvent>({
						.mouse_pos = {adjusted_mouse.x, adjusted_mouse.y},
						.button = event.data.mouse_data.mouse_button,
					});
					this->last_mouse_down_position = {adjusted_mouse.x, adjusted_mouse.y};
					this->last_mouse_button = event.data.mouse_data.mouse_button;
					break;

				case SDLContext::EventType::MOUSEUP: {
					event_mgr.queue_event<MouseReleaseEvent>({
						.mouse_pos = {adjusted_mouse.x, adjusted_mouse.y},
						.button = event.data.mouse_data.mouse_button,
					});
					int delta_x = adjusted_mouse.x - this->last_mouse_down_position.x;
					int delta_y = adjusted_mouse.y - this->last_mouse_down_position.y;

					if (this->last_mouse_button == event.data.mouse_data.mouse_button
						&& std::abs(delta_x) <= click_tolerance
						&& std::abs(delta_y) <= click_tolerance) {
						event_mgr.queue_event<MouseClickEvent>({
							.mouse_pos = {adjusted_mouse.x, adjusted_mouse.y},
							.button = event.data.mouse_data.mouse_button,
						});
						this->handle_click(event.data.mouse_data.mouse_button, adjusted_mouse);
					}
					break;
				}

				case SDLContext::EventType::MOUSEMOVE:
					event_mgr.queue_event<MouseMoveEvent>({
						.mouse_pos = {adjusted_mouse.x, adjusted_mouse.y},
						.mouse_delta = event.data.mouse_data.rel_mouse_move,
					});
					this->handle_move(event, adjusted_mouse);
					break;

				case SDLContext::EventType::MOUSEWHEEL:
					event_mgr.queue_event<MouseScrollEvent>({
						.mouse_pos = {adjusted_mouse.x, adjusted_mouse.y},
						.scroll_direction = event.data.mouse_data.scroll_direction,
						.scroll_delta = event.data.mouse_data.scroll_delta,
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
						{.repeat = event.data.key_data.key_repeat, .key = event.data.key_data.key});
					break;
				case SDLContext::EventType::KEYUP:
					event_mgr.queue_event<KeyReleaseEvent>({.key = event.data.key_data.key});
					break;
				case SDLContext::EventType::SHUTDOWN:
					event_mgr.queue_event<ShutDownEvent>({});
					break;
				case SDLContext::EventType::WINDOW_EXPOSE:
					event_mgr.queue_event<WindowExposeEvent>({});
					break;
				case SDLContext::EventType::WINDOW_RESIZE:
					event_mgr.queue_event<WindowResizeEvent>(
						WindowResizeEvent{.dimensions = event.data.window_data.resize_dimension});
					break;
				case SDLContext::EventType::WINDOW_MOVE:
					event_mgr.queue_event<WindowMoveEvent>(
						{.delta_move = event.data.window_data.move_delta});
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
							  const ivec2& mouse_pos) {
	ComponentManager & mgr = this->mediator.component_manager;

	RefVector<Button> buttons = mgr.get_components_by_type<Button>();

	for (Button & button : buttons) {
		if(!button.active) continue;
		RefVector<Transform> transform_vec
			= mgr.get_components_by_id<Transform>(button.game_object_id);
		Transform & transform(transform_vec.front().get());

		bool was_hovering = button.hover;
		if (this->is_mouse_inside_button(mouse_pos, button,
											transform)) {
			button.hover = true;
			if(!button.on_mouse_enter) continue;
			if (!was_hovering) {
				button.on_mouse_enter();
			}
		} else {
			button.hover = false;
			// Trigger the on_exit callback if the hover state just changed to false
			if(!button.on_mouse_exit) continue;
			if (was_hovering) {
				button.on_mouse_exit();
			}
		}
	}
}

void InputSystem::handle_click(const MouseButton & mouse_button, const ivec2& mouse_pos) {
	ComponentManager & mgr = this->mediator.component_manager;

	RefVector<Button> buttons = mgr.get_components_by_type<Button>();

	for (Button & button : buttons) {
		if(!button.active) continue;
		if (!button.on_click) continue;
		RefVector<Transform> transform_vec
			= mgr.get_components_by_id<Transform>(button.game_object_id);
		Transform & transform = transform_vec.front().get();
		
		if (this->is_mouse_inside_button(mouse_pos, button,
											transform)) {
			 
			button.on_click();
		}
	}
}

bool InputSystem::is_mouse_inside_button(const ivec2& mouse_pos,
										 const Button & button, const Transform & transform) {
	int actual_x = transform.position.x + button.offset.x;
	int actual_y = transform.position.y + button.offset.y;

	int half_width = button.dimensions.x / 2;
	int half_height = button.dimensions.y / 2;

	// Check if the mouse is within the button's boundaries
	return mouse_pos.x >= actual_x - half_width && mouse_pos.x <= actual_x + half_width
		   && mouse_pos.y >= actual_y - half_height && mouse_pos.y <= actual_y + half_height;
}

