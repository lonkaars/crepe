#pragma once

#include "../Component.h"

namespace crepe {

/**
 * \brief Represents a UI object in the game, derived from the Component class.
 */
class UIObject : public Component {
public:
	/**
	 * \brief Constructs a UiObject with the specified game object ID.
	 * \param id The unique ID of the game object associated with this UI object.
	 * \param dimensions width and height of the UIObject
	 * \param offset Offset relative to the GameObject Transform
	 */
	UIObject(game_object_id_t id, const vec2 & dimensions, const vec2 & offset = {0, 0});
	//! Width and height of the UIObject
	vec2 dimensions;
	//! Position offset relative to this GameObjects Transform
	vec2 offset;
};

} // namespace crepe
