#pragma once

#include "api/Transform.h"

#include "types.h"

namespace crepe {

/**
 * \brief A class for calculating the absolute position of an object.
 *
 * This class provides a utility function to get the position of an object in the world space,
 * taking into account the transform and any additional offset.
 */
class AbsolutePosition {
public:
	/**
	 * \brief Get the absolute position of an object.
	 *
	 * This function calculates the absolute position by combining the transform position with an optional offset.
	 *
	 * \param transform The transform of the object, which contains its position, rotation, and scale.
	 * \param offset The offset to apply to the object's position (in local space).
	 * \return The absolute position of the object as a 2D vector.
	 */
	static vec2 get_position(const Transform & transform, const vec2 & offset);
};

} // namespace crepe
