#pragma once

#include <cstdint>

#include "api/Point.h"

#include "Component.h"

namespace crepe {

/**
 * \brief Transform component
 * 
 * This class represents the Transform component. It stores the position,
 * rotation and scale of a GameObject.
 */
class Transform : public Component {
public:
	/**
	 * \param id The id of the GameObject this component belongs to
	 * \param point The position of the GameObject
	 * \param rot The rotation of the GameObject
	 * \param scale The scale of the GameObject
	 */
	Transform(uint32_t id, const Point & point, double rot, double scale);
	~Transform();
	/**
	 * \brief Get the maximum number of instances for this component
	 *
	 * \return The maximum number of instances for this component
	 */
	virtual int get_instances_max() const { return 1; }

public:
	//! Translation (shift)
	Point position;
	//! Rotation, in radians
	double rotation;
	//! Multiplication factor
	double scale;
};

} // namespace crepe
