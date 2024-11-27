#pragma once

#include <functional>
#include "UiObject.h"

namespace crepe {

/**
 * \class Button
 * \brief Represents a clickable UI button, derived from the UiObject class.
 * 
 * This class provides functionality for a button in the UI, including toggle state,
 * click handling, and mouse hover detection. A callback function can be provided to
 * handle button clicks.
 */
class Button : public UiObject {
public:
	/**
     * \brief Constructs a Button with the specified game object ID and dimensions.
     * 
     * \param id The unique ID of the game object associated with this button.
     * \param width The width of the button.
     * \param height The height of the button.
     * \param is_toggle Optional flag to indicate if the button is a toggle button. Defaults to false.
     * \param on_click callback function that will be invoked when the button is clicked.
     */
	Button(game_object_id_t id, int width, int height, bool is_toggle = false, std::function<void()> on_click = nullptr);

	/**
     * \brief Indicates if the button is a toggle button (can be pressed and released).
     * 
     * A toggle button allows for a pressed/released state, whereas a regular button
     * typically only has an on-click state.
     */
	bool is_toggle;

	/**
     * \brief Indicates whether the button is currently pressed.
     * 
     * This state is true when the button is actively pressed and false otherwise.
     */
	bool is_pressed;

	/**
     * \brief Indicates whether the mouse is currently hovering over the button.
     * 
     * This is set to true when the mouse is over the button and false otherwise.
     */
	bool hover;

	/**
     * \brief The callback function to be executed when the button is clicked.
     * 
     * This function is invoked whenever the button is clicked. It can be set to any
     * function that matches the signature `void()`. Defaults to nullptr.
     */
	std::function<void()> on_click;

public:
	/**
     * \brief Retrieves the maximum number of instances allowed for this button type.
     * 
     * \return Always returns 1, as only a single instance of this type is allowed.
     */
	virtual int get_instances_max() const override { return 1; }
};

} // namespace crepe
