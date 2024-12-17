#pragma once

#include "../api/Config.h"
#include "../facade/EventData.h"

#include "../api/Event.h"
#include "../api/Metadata.h"
#include "../types.h"
#include "../util/OptionalRef.h"

#include "System.h"

namespace crepe {

class Camera;
class Button;
class Transform;
/**
 * \brief Event triggered during a collision between objects.
 */
class ButtonPressEvent : public Event {
public:
	const Metadata & meta_data;
	ButtonPressEvent(const Metadata & meta_data) : meta_data(meta_data){};
};
class ButtonEnterEvent : public Event {
public:
	const Metadata & meta_data;
	ButtonEnterEvent(const Metadata & meta_data) : meta_data(meta_data){};
};
class ButtonExitEvent : public Event {
public:
	const Metadata & meta_data;
	ButtonExitEvent(const Metadata & meta_data) : meta_data(meta_data){};
};

/**
 * \brief Handles the processing of input events created by SDLContext
 *
 * This system processes events such as mouse clicks, mouse movement, and keyboard
 * actions. It is responsible for detecting interactions with UI buttons and
 * passing the corresponding events to the registered listeners.
 */
class InputSystem : public System {
public:
	using System::System;

	/**
	 * \brief Updates the system, processing all input events.
	 * This method processes all events and triggers corresponding actions.
	 */
	void update() override;

private:
	//! Stores the last position of the mouse when the button was pressed.
	vec2 last_mouse_down_position;
	// TODO: specify world/hud space and make regular `vec2`

	//! Stores the last mouse button pressed.
	MouseButton last_mouse_button = MouseButton::NONE;
	/**
	 * \brief Handles mouse-related events.
	 * \param event The event data for the mouse event.
	 * \param camera_origin The origin position of the camera in world space.
	 * \param current_cam The currently active camera.
	 *
	 * This method processes mouse events, adjusts the mouse position to world coordinates,
	 * and triggers the appropriate mouse-specific event handling logic.
	 */
	void handle_mouse_event(const EventData & event, const vec2 & camera_origin,
							const Camera & current_cam);
	/**
	 * \brief Handles non-mouse-related events.
	 * \param event The event data for the non-mouse event.
	 *
	 * This method processes events that do not involve the mouse, such as keyboard events,
	 * window events, and shutdown events, and triggers the corresponding event actions.
	 */
	void handle_non_mouse_event(const EventData & event);
	/**
	* \brief Handles the mouse click event.
	* \param mouse_button The mouse button involved in the click.
	* \param world_mouse_x The X coordinate of the mouse in world space.
	* \param world_mouse_y The Y coordinate of the mouse in world space.
	*
	* This method processes the mouse click event and triggers the corresponding button action.
	*/
	void handle_click(const MouseButton & mouse_button, const vec2 & mouse_pos);

	/**
	* \brief Handles the mouse movement event.
	* \param event_data The event data containing information about the mouse movement.
	* \param world_mouse_x The X coordinate of the mouse in world space.
	* \param world_mouse_y The Y coordinate of the mouse in world space.
	*
	* This method processes the mouse movement event and updates the button hover state.
	*/
	void handle_move(const EventData & event_data, const vec2 & mouse_pos);

	/**
	* \brief Checks if the mouse position is inside the bounds of the button.
	* \param world_mouse_x The X coordinate of the mouse in world space.
	* \param world_mouse_y The Y coordinate of the mouse in world space.
	* \param button The button to check.
	* \param transform The transform component of the button.
	* \return True if the mouse is inside the button, false otherwise.
	*/
	bool is_mouse_inside_button(const vec2 & mouse_pos, const Button & button,
								const Transform & transform);

	/**
	* \brief Handles the button press event, calling the on_click callback if necessary.
	* \param button The button being pressed.
	*
	* This method triggers the on_click action for the button when it is pressed.
	*/
	void handle_button_press(Button & button);
};

} // namespace crepe
