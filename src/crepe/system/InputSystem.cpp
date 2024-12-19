#include "../api/Button.h"
#include "../facade/SDLContext.h"
#include "../manager/ComponentManager.h"
#include "../manager/EventManager.h"
#include "util/Log.h"

#include "InputSystem.h"

using namespace crepe;

void InputSystem::update() {
	ComponentManager & mgr = this->mediator.component_manager;

	SDLContext & context = this->mediator.sdl_context;
	std::vector<EventData> event_list = context.get_events();
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
	Transform & cam_transform
		= mgr.get_components_by_id<Transform>(current_cam.game_object_id).front();

	vec2 camera_origin = cam_transform.position + current_cam.data.postion_offset
						 - (current_cam.viewport_size / 2);

	for (const EventData & event : event_list) {
		// Only calculate mouse coordinates for relevant events
		if (event.event_type == EventType::MOUSE_DOWN
			|| event.event_type == EventType::MOUSE_UP
			|| event.event_type == EventType::MOUSE_MOVE
			|| event.event_type == EventType::MOUSE_WHEEL) {
			this->handle_mouse_event(event, camera_origin, current_cam);

		} else {
			this->handle_non_mouse_event(event);
		}
	}
}

void InputSystem::handle_mouse_event(const EventData & event, const vec2 & camera_origin,
									 const Camera & current_cam) {
	EventManager & event_mgr = this->mediator.event_manager;
	vec2 adjusted_mouse;
	adjusted_mouse.x = event.data.mouse_data.mouse_position.x + camera_origin.x;
	adjusted_mouse.y = event.data.mouse_data.mouse_position.y + camera_origin.y;
	// Check if the mouse is within the viewport
	if ((adjusted_mouse.x < camera_origin.x
		 || adjusted_mouse.x > camera_origin.x + current_cam.viewport_size.x
		 || adjusted_mouse.y < camera_origin.y
		 || adjusted_mouse.y > camera_origin.y + current_cam.viewport_size.y))
		return;

	// Handle mouse-specific events
	switch (event.event_type) {
		case EventType::MOUSE_DOWN:
			event_mgr.queue_event<MousePressEvent>({
				.mouse_pos = adjusted_mouse,
				.button = event.data.mouse_data.mouse_button,
			});
			this->last_mouse_down_position = adjusted_mouse;
			this->last_mouse_button = event.data.mouse_data.mouse_button;
			break;

		case EventType::MOUSE_UP: {
			event_mgr.queue_event<MouseReleaseEvent>({
				.mouse_pos = adjusted_mouse,
				.button = event.data.mouse_data.mouse_button,
			});
			vec2 delta_move = adjusted_mouse - this->last_mouse_down_position;
			int click_tolerance = Config::get_instance().input.click_tolerance;
			if (this->last_mouse_button == event.data.mouse_data.mouse_button
				&& std::abs(delta_move.x) <= click_tolerance
				&& std::abs(delta_move.y) <= click_tolerance) {
				event_mgr.queue_event<MouseClickEvent>({
					.mouse_pos = adjusted_mouse,
					.button = event.data.mouse_data.mouse_button,
				});
				this->handle_click(event.data.mouse_data.mouse_button, adjusted_mouse,
								   current_cam);
			}
			break;
		}

		case EventType::MOUSE_MOVE:
			event_mgr.queue_event<MouseMoveEvent>({
				.mouse_pos = adjusted_mouse,
				.mouse_delta = event.data.mouse_data.rel_mouse_move,
			});
			this->handle_move(event, adjusted_mouse, current_cam);
			break;

		case EventType::MOUSE_WHEEL:
			event_mgr.queue_event<MouseScrollEvent>({
				.mouse_pos = adjusted_mouse,
				.scroll_direction = event.data.mouse_data.scroll_direction,
				.scroll_delta = event.data.mouse_data.scroll_delta,
			});
			break;

		default:
			break;
	}
}

void InputSystem::handle_non_mouse_event(const EventData & event) {
	EventManager & event_mgr = this->mediator.event_manager;
	switch (event.event_type) {
		case EventType::KEY_DOWN:

			event_mgr.queue_event<KeyPressEvent>(
				{.repeat = event.data.key_data.key_repeat, .key = event.data.key_data.key});
			break;
		case EventType::KEY_UP:
			event_mgr.queue_event<KeyReleaseEvent>({.key = event.data.key_data.key});
			break;
		case EventType::SHUTDOWN:
			event_mgr.queue_event<ShutDownEvent>({});
			break;
		case EventType::WINDOW_EXPOSE:
			event_mgr.queue_event<WindowExposeEvent>({});
			break;
		case EventType::WINDOW_RESIZE:
			event_mgr.queue_event<WindowResizeEvent>(
				WindowResizeEvent{.dimensions = event.data.window_data.resize_dimension});
			break;
		case EventType::WINDOW_MOVE:
			event_mgr.queue_event<WindowMoveEvent>(
				{.delta_move = event.data.window_data.move_delta});
			break;
		case EventType::WINDOW_MINIMIZE:
			event_mgr.queue_event<WindowMinimizeEvent>({});
			break;
		case EventType::WINDOW_MAXIMIZE:
			event_mgr.queue_event<WindowMaximizeEvent>({});
			break;
		case EventType::WINDOW_FOCUS_GAIN:
			event_mgr.queue_event<WindowFocusGainEvent>({});
			break;
		case EventType::WINDOW_FOCUS_LOST:
			event_mgr.queue_event<WindowFocusLostEvent>({});
			break;
		default:
			break;
	}
}

void InputSystem::handle_move(const EventData & event_data, const vec2 & mouse_pos,
							  const Camera & current_cam) {
	ComponentManager & mgr = this->mediator.component_manager;

	RefVector<Button> buttons = mgr.get_components_by_type<Button>();

	for (Button & button : buttons) {
		if (!button.active) continue;

		Transform & transform
			= mgr.get_components_by_id<Transform>(button.game_object_id).front();
		Transform & cam_transform
			= mgr.get_components_by_id<Transform>(current_cam.game_object_id).front();
		bool was_hovering = button.hover;

		if (this->is_mouse_inside_button(mouse_pos, button, transform, cam_transform)) {
			button.hover = true;
			if (!button.on_mouse_enter) continue;
			if (!was_hovering) {
				button.on_mouse_enter();
			}
		} else {
			button.hover = false;
			// Trigger the on_exit callback if the hover state just changed to false
			if (!button.on_mouse_exit) continue;
			if (was_hovering) {
				button.on_mouse_exit();
			}
		}
	}
}

void InputSystem::handle_click(const MouseButton & mouse_button, const vec2 & mouse_pos,
							   const Camera & current_cam) {
	ComponentManager & mgr = this->mediator.component_manager;

	RefVector<Button> buttons = mgr.get_components_by_type<Button>();
	Transform & cam_transform
		= mgr.get_components_by_id<Transform>(current_cam.game_object_id).front();
	for (Button & button : buttons) {
		if (!button.active) continue;
		if (!button.on_click) continue;
		RefVector<Transform> transform_vec
			= mgr.get_components_by_id<Transform>(button.game_object_id);
		Transform & transform = transform_vec.front().get();

		if (this->is_mouse_inside_button(mouse_pos, button, transform, cam_transform)) {
			button.on_click();
		}
	}
}

bool InputSystem::is_mouse_inside_button(const vec2 & mouse_pos, const Button & button,
										 const Transform & transform,
										 const Transform & cam_transform) {
	vec2 actual_pos = transform.position + button.offset;
	if (!button.world_space) {
		actual_pos += cam_transform.position;
	}
	vec2 half_dimensions = button.dimensions / 2;

	return mouse_pos.x >= actual_pos.x - half_dimensions.x
		   && mouse_pos.x <= actual_pos.x + half_dimensions.x
		   && mouse_pos.y >= actual_pos.y - half_dimensions.y
		   && mouse_pos.y <= actual_pos.y + half_dimensions.y;
}
