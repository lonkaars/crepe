#pragma once

#include "types.h"

#include <cstdint>

namespace crepe {

class ComponentManager;

/**
 * \brief Base class for all components
 * 
 * This class is the base class for all components. It provides a common
 * interface for all components.
 */
class Component {
protected:
	//! Only the ComponentManager can create components
	friend class crepe::ComponentManager;
	/**
	 * \param id The id of the GameObject this component belongs to
	 */
	Component(game_object_id_t id);

public:
	virtual ~Component() = default;
	/**
	 * \brief Get the maximum number of instances for this component
	 *
	 * This method returns -1 by default, which means that there is no limit
	 * for the number of instances. Concrete components can override this method
	 * to set a limit.
	 *
	 * \return The maximum number of instances for this component
	 */
	virtual int get_instances_max() const { return -1; }

public:
	//! The id of the GameObject this component belongs to
	const game_object_id_t game_object_id;
	//! Whether the component is active
	bool active = true;
};

} // namespace crepe
