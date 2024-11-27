#pragma once

#include "../Component.h"

namespace crepe {

/**
 * @class UiObject
 * \brief Represents a UI object in the game, derived from the Component class.
 */
class UiObject : public Component {
public:
	/**
     * \brief Constructs a UiObject with the specified game object ID.
     * \param id The unique ID of the game object associated with this UI object.
     */
	UiObject(game_object_id_t id,int width,int height);

	//! The width of the UI object.
	int width = 0;

	//! The height of the UI object.
	int height = 0;

public:
	/**
     * \brief Retrieves the maximum number of instances allowed for this UI object type.
     * /return Always returns 1, as only a single instance is allowed.
     */
	virtual int get_instances_max() const override { return 1; }
};

} // namespace crepe
