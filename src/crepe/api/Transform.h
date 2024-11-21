#pragma once

#include "api/Vector2.h"

#include "Component.h"

namespace crepe {

/**
 * \brief Transform component
 * 
 * This class represents the Transform component. It stores the position, rotation and scale of
 * a GameObject.
 */
class Transform : public Component {
public:
	//! Translation (shift)
	Vector2<double> position = {0, 0};
	//! Rotation, in degrees
	double rotation = 0;
	//! Multiplication factor
	double scale = 0;

protected:
	/**
	 * \param id The id of the GameObject this component belongs to
	 * \param point The position of the GameObject
	 * \param rotation The rotation of the GameObject
	 * \param scale The scale of the GameObject
	 */
	Transform(game_object_id_t id, const Vector2<double> & point, double rotation,
			  double scale);
	/**
	 * There is always exactly one transform component per entity
	 * \return 1
	 */
	virtual int get_instances_max() const { return 1; }
	//! ComponentManager instantiates all components
	friend class ComponentManager;
};

} // namespace crepe
