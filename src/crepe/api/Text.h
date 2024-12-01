#pragma once

#include <string>

#include "Color.h"
#include "UiObject.h"
#include ""
namespace crepe {

/**
 * \class Button
 * \brief Represents a clickable UI button, derived from the UiObject class.
 * 
 * This class provides functionality for a button in the UI, including toggle state,
 * click handling, and mouse hover detection. A callback function can be provided to
 * handle button clicks.
 */
class Text : public UiObject {
public:
	/**
     * \brief Constructs a Button with the specified game object ID and dimensions.
     * 
     * \param id The unique ID of the game object associated with this button.
     * \param width The width of the button.
     * \param height The height of the button.
     */
	Text(game_object_id_t id, int width, int height);

	Color color = Color{0,0,0,0};
	std::string text = "";
	int size = 0;
	const std::shared_ptr<Font> sprite_image;
public:
	/**
     * \brief Retrieves the maximum number of instances allowed for this button type.
     * 
     * \return Always returns 1, as only a single instance of this type is allowed.
     */
	virtual int get_instances_max() const override { return 10; }
};

} // namespace crepe
