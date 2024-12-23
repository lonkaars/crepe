#pragma once

#include "Component.h"
#include "types.h"

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
	vec2 position = {0, 0};
	//! Rotation, in degrees clockwise
	float rotation = 0;
	//! Multiplication factor
	float scale = 0;

protected:
	/**
	 * \param id The id of the GameObject this component belongs to
	 * \param point The position of the GameObject
	 * \param rotation The rotation of the GameObject
	 * \param scale The scale of the GameObject
	 */
	Transform(game_object_id_t id, const vec2 & point, double rotation, double scale);
	/**
	 * There is always exactly one transform component per entity
	 * \return 1
	 */
	virtual int get_instances_max() const { return 1; }
	//! ComponentManager instantiates all components
	friend class ComponentManager;

protected:
	virtual std::unique_ptr<Component> save() const;
	Transform(const Transform &) = default;
	virtual void restore(const Component & snapshot);
	virtual Transform & operator=(const Transform &) = default;
};

} // namespace crepe
