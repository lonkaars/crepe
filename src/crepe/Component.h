#pragma once

#include <memory>

#include "types.h"

namespace crepe {

class ComponentManager;

/**
 * \brief Base class for all components
 *
 * This class is the base class for all components. It provides a common interface for all
 * components.
 */
class Component {
public:
	//! Whether the component is active
	bool active = true;
	/**
	 * \brief The id of the GameObject this component belongs to
	 *
	 * \note Only systems are supposed to use this member, but since friend
	 * relations aren't inherited this needs to be public.
	 */
	const game_object_id_t game_object_id;

protected:
	/**
	 * \param id The id of the GameObject this component belongs to
	 */
	Component(game_object_id_t id);
	//! Only ComponentManager can create components
	friend class ComponentManager;

	// components are never moved
	Component(Component &&) = delete;
	virtual Component & operator=(Component &&) = delete;

protected:
	virtual std::unique_ptr<Component> save() const;
	Component(const Component &) = default;
	virtual void restore(const Component & snapshot);
	virtual Component & operator=(const Component &);

public:
	virtual ~Component() = default;

public:
	/**
	 * \brief Get the maximum number of instances for this component
	 *
	 * This method returns -1 by default, which means that there is no limit for the number of
	 * instances. Concrete components can override this method to set a limit.
	 *
	 * \return The maximum number of instances for this component
	 */
	virtual int get_instances_max() const { return -1; }
};

} // namespace crepe
