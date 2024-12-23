#pragma once

#include <cmath>
#include <set>
#include <string>

#include "../Component.h"

#include "types.h"

namespace crepe {

/**
 * \brief Rigidbody class
 *
 * This class is used by the physics sytem and collision system. It configures how to system
 * interact with the gameobject for movement and collisions.
 */
class Rigidbody : public Component {
public:
	/**
	 * \brief BodyType enum
	 *
	 * This enum provides three bodytypes the physics sytem and collision system use.
	 */
	enum class BodyType {
		//! Does not move (e.g. walls, ground ...)
		STATIC,
		//! Moves and responds to forces (e.g. player, physics objects ...)
		DYNAMIC,
		//! Moves but does not respond to forces (e.g. moving platforms ...)
		KINEMATIC,
	};
	/**
	 * \brief PhysicsConstraints to constrain movement
	 *
	 * This struct configures the movement constraint for this object. If a constraint is enabled
	 * the systems will not move the object.
	 */
	struct PhysicsConstraints {
		//! Prevent movement along X axis
		bool x = false;
		//! Prevent movement along Y axis
		bool y = false;
		//! Prevent rotation
		bool rotation = false;
	};

public:
	/**
	 * \brief struct for Rigidbody data
	 *
	 * This struct holds the data for the Rigidbody.
	 */
	struct Data {
		//! objects mass
		float mass = 1;
		/**
		* \brief Gravity scale factor.
		*
		* The `gravity_scale` controls how much gravity affects the object. It is a multiplier applied to the default
		* gravity force, allowing for fine-grained control over how the object responds to gravity.
		*
		*/
		float gravity_scale = 0;

		//! Defines the type of the physics body, which determines how the physics system interacts with the object.
		BodyType body_type = BodyType::DYNAMIC;

		/**
		* \name Linear (positional) motion
		*
		* These variables define the linear motion (movement along the position) of an object.
		* The linear velocity is applied to the object's position in each update of the PhysicsSystem.
		* The motion is affected by the object's linear velocity, its maximum velocity, and a coefficient
		* that can scale the velocity over time.
		*
		* \{
		*/
		//! Linear velocity of the object (speed and direction).
		vec2 linear_velocity;
		//! Maximum linear velocity of the object. This limits the object's speed.
		float max_linear_velocity = INFINITY;
		//! Linear velocity coefficient. This scales the object's velocity for adjustment or damping.
		vec2 linear_velocity_coefficient = {1, 1};
		//! \}

		/**
		* \name Angular (rotational) motion
		*
		* These variables define the angular motion (rotation) of an object.
		* The angular velocity determines how quickly the object rotates, while the maximum angular velocity
		* sets a limit on the rotation speed. The angular velocity coefficient applies damping or scaling
		* to the angular velocity, which can be used to simulate friction or other effects that slow down rotation.
		*
		* \{
		*/
		//! Angular velocity of the object, representing the rate of rotation (in degrees).
		float angular_velocity = 0;
		//! Maximum angular velocity of the object. This limits the maximum rate of rotation.
		float max_angular_velocity = INFINITY;
		//! Angular velocity coefficient. This scales the object's angular velocity, typically used for damping.
		float angular_velocity_coefficient = 1;
		//! \}

		/**
		* \brief Movement constraints for an object.
		*
		* The `PhysicsConstraints` struct defines the constraints that restrict an object's movement
		* in certain directions or prevent rotation. These constraints effect only the physics system
		* to prevent the object from moving or rotating in specified ways.
		*
		*/
		PhysicsConstraints constraints;

		/**
		* \brief Elasticity factor of the material (bounce factor).
		*
		* The `elasticity_coefficient` controls how much of the object's velocity is retained after a collision.
		* It represents the material's ability to bounce or recover velocity upon impact. The coefficient is a value
		* above 0.0.
		*
		*/
		float elasticity_coefficient = 0.0;

		/**
		 * \brief  Enables collision handling for objects colliding with kinematic objects.
		 *
		 * Enables collision handling for objects colliding with kinematic objects in the collision system.
     * If `kinematic_collision` is true, dynamic objects cannot pass through this kinematic object.
     * This ensures that kinematic objects delegate collision handling to the collision system.
		 */
		bool kinematic_collision = true;

		/**
		* \brief Defines the collision layers a GameObject interacts with.
		*
		* The `collision_layers` represent the set of layers the GameObject can detect collisions with.
		* Each element in this set corresponds to a layer ID. The GameObject will only collide with other
		* GameObjects that belong to one these layers.
		*/
		std::set<int> collision_layers = {0};

		/**
		* \brief Specifies the collision layer of the GameObject.
		*
		* The `collision_layer` indicates the single layer that this GameObject belongs to. 
		* This determines which layers other objects must match to detect collisions with this object.
		*/
		int collision_layer = 0;

		/**
		 * \brief Defines the collision layers of a GameObject.
		 *
		 * The `collision_names` specifies where the GameObject will collide with.
		 * Each element represents a name from the Metadata of the gameobject.
		 */
		std::set<std::string> collision_names;

		/**
		 * \brief Defines the collision layers of a GameObject.
		 *
		 * The `collision_tags` specifies where the GameObject will collide with.
		 * Each element represents a tag from the Metadata of the gameobject.
		 */
		std::set<std::string> collision_tags;
	};

public:
	/**
	 * \param game_object_id id of the gameobject the rigibody is added to.
	 * \param data struct to configure the rigidbody.
	 */
	Rigidbody(game_object_id_t id, const Data & data);
	//! struct to hold data of rigidbody
	Data data;

public:
	/**
	 * \brief add a linear force to the Rigidbody.
	 *
	 * \param force Vector2 that is added to the linear force.
	 */
	void add_force_linear(const vec2 & force);
	/**
	 * \brief add a angular force to the Rigidbody.
	 *
	 * \param force Vector2 that is added to the angular force.
	 */
	void add_force_angular(float force);

protected:
	/**
	* Ensures there is at most one Rigidbody component per entity.
	* \return Always returns 1, indicating this constraint.
	*/
	virtual int get_instances_max() const { return 1; }
	//! ComponentManager instantiates all components
	friend class ComponentManager;
};

} // namespace crepe
