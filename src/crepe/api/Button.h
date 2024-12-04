#pragma once

#include <functional>

#include "UiObject.h"

namespace crepe {

/**
 * \brief Represents a clickable UI button, derived from the UiObject class.
 * 
 */
class Button : public UIObject {
public:
	/**
     * \brief Constructs a Button with the specified game object ID and dimensions.
     * 
     * \param id The unique ID of the game object associated with this button.
     * \param Dimensions The width and height of the UIObject
     * \param offset The offset relative this GameObjects Transform
     * \param is_toggle Optional flag to indicate if the button is a toggle button. Defaults to false.
     * \param on_click callback function that will be invoked when the button is clicked.
     */
	Button(game_object_id_t id, vec2 dimensions,vec2 offset, std::function<void()> on_click,
		   bool is_toggle = false);

	/**
     * \brief Indicates if the button is a toggle button (can be pressed and released).
     * 
     * A toggle button allows for a pressed/released state, whereas a regular button
     * typically only has an on-click state.
     */
	bool is_toggle = false;

	/**
     * \brief The callback function to be executed when the button is clicked.
     * 
     * This function is invoked whenever the button is clicked. It can be set to any
     * function that matches the signature `void()`.
     */
	std::function<void()> on_click = nullptr;

	/**
	 * \brief Callback function to be executed when the mouse enters the button's boundaries.
	 *
	 * This function is triggered when the mouse cursor moves over the button, allowing
	 * custom actions like visual effects, highlighting, or sound effects.
	 */
	std::function<void()> on_mouse_enter = nullptr;

	/**
	 * \brief Callback function to be executed when the mouse exits the button's boundaries.
	 *
	 * This function is triggered when the mouse cursor moves out of the button's area,
	 * allowing custom actions like resetting visual effects or playing exit-related effects.
	 */
	std::function<void()> on_mouse_exit = nullptr;

private:
	//! friend relation for is_pressed and hover variables
	friend class InputSystem;
	/**
     * \brief Indicates whether the toggle button is pressed
     * 
     *  This state indicates if the toggle button is pressed or not
     */
	bool is_pressed = false;

	/**
     * \brief Indicates whether the mouse is currently hovering over the button.
     * 
     * This is set to true when the mouse is over the button and false otherwise.
     */
	bool hover = false;

public:
};

} // namespace crepe
