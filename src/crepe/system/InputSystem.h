#pragma once

#include "../facade/SDLContext.h"
#include "../types.h"
#include "../util/OptionalRef.h"
#include "../api/Config.h"

#include "System.h"

namespace crepe {

class Camera;
class Button;
class Transform;

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
	ivec2 last_mouse_down_position;
	// TODO: specify world/hud space and make regular `vec2`

	//! Stores the last mouse button pressed.
	MouseButton last_mouse_button = MouseButton::NONE;

	//! The maximum allowable distance between mouse down and mouse up to register as a click. This can be changed using the Config.
	int click_tolerance = Config::get_instance().click_tolerance.tolerance;

	/**
	* \brief Handles the mouse click event.
	* \param mouse_button The mouse button involved in the click.
	* \param world_mouse_x The X coordinate of the mouse in world space.
	* \param world_mouse_y The Y coordinate of the mouse in world space.
	*
	* This method processes the mouse click event and triggers the corresponding button action.
	*/
	void handle_click(const MouseButton & mouse_button, const int world_mouse_x,
					  const int world_mouse_y);

	/**
	* \brief Handles the mouse movement event.
	* \param event_data The event data containing information about the mouse movement.
	* \param world_mouse_x The X coordinate of the mouse in world space.
	* \param world_mouse_y The Y coordinate of the mouse in world space.
	*
	* This method processes the mouse movement event and updates the button hover state.
	*/
	void handle_move(const SDLContext::EventData & event_data, const int world_mouse_x,
					 const int world_mouse_y);

	/**
	* \brief Checks if the mouse position is inside the bounds of the button.
	* \param world_mouse_x The X coordinate of the mouse in world space.
	* \param world_mouse_y The Y coordinate of the mouse in world space.
	* \param button The button to check.
	* \param transform The transform component of the button.
	* \return True if the mouse is inside the button, false otherwise.
	*/
	bool is_mouse_inside_button(const int world_mouse_x, const int world_mouse_y,
								const Button & button, const Transform & transform);

	/**
	* \brief Handles the button press event, calling the on_click callback if necessary.
	* \param button The button being pressed.
	*
	* This method triggers the on_click action for the button when it is pressed.
	*/
	void handle_button_press(Button & button);
};

} // namespace crepe
