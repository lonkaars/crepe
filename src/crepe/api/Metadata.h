#pragma once

#include <string>
#include <vector>

#include "../Component.h"

namespace crepe {

/**
 * \brief Metadata component
 * 
 * This class represents the Metadata component. It stores the name, tag, parent
 * and children of a GameObject.
 */
class Metadata : public Component {
public:
	/**
	 * \param game_object_id The id of the GameObject this component belongs to
	 * \param name The name of the GameObject
	 * \param tag The tag of the GameObject
	 */
	Metadata(const Component::Data & data, const std::string & name,
			 const std::string & tag);
	/**
	 * \brief Get the maximum number of instances for this component
	 *
	 * \return The maximum number of instances for this component
	 */
	virtual int get_instances_max() const { return 1; }

public:
	//! The name of the GameObject
	const std::string name;
	//! The tag of the GameObject
	const std::string tag;
	//! The id of the parent GameObject (-1 if no parent)
	game_object_id_t parent = -1;
	//! The ids of the children GameObjects
	std::vector<game_object_id_t> children;
};

} // namespace crepe
