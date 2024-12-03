#pragma once

#include <cmath>

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
		float mass = 0.0;
		/**
		* \brief Gravity scale factor.
		*
		* The `gravity_scale` controls how much gravity affects the object. It is a multiplier applied to the default
		* gravity force, allowing for fine-grained control over how the object responds to gravity.
		* 
		* - A value of `0.0` means that gravity has **no effect** on the object (i.e., the object is completely immune to gravity).
		* - A value of `1.0` means that gravity is applied at its **normal intensity** (the default behavior).
		* - A value greater than `1.0` means the object is affected by gravity more strongly than normal.
		* - A value less than `1.0` (but greater than `0.0`) reduces the effect of gravity on the object.
		* 
		* This is useful in cases where you need objects to behave differently under gravity, such as lighter objects (like feathers),
		* objects that float in water, or heavier objects that fall faster.
		*/
		float gravity_scale = 0;
		/**
		* \brief Defines the type of the physics body, which determines how the physics system interacts with the object.
		*
		* - **Static**: The object does not move and is not affected by forces. It is used for immovable objects like walls or terrain. Does not have collision detection.
		* - **Dynamic**: The object is fully affected by physics forces, including gravity, collisions, and other physical interactions. It can move and be moved by forces.
		* - **Kinematic**: The object does not move and is not affected by forces. It is typically controlled by external factors (e.g., animations or user input), and collision detection is handled without affecting its velocity.
		*
		* The `body_type` defines the behavior of the object in the physics system.
		*
		* \default BodyType::DYNAMIC
		*/
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
		vec2 max_linear_velocity = {INFINITY ,INFINITY};
		//! Linear velocity coefficient. This scales the object's velocity for adjustment or damping.
		vec2 linear_velocity_coefficient = {1,1};
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
		//! Angular velocity of the object, representing the rate of rotation (in radians per second).
		float angular_velocity = 1;
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
		* - **X Constraint**: If enabled, the object cannot move along the X-axis.
		* - **Y Constraint**: If enabled, the object cannot move along the Y-axis.
		* - **Rotation Constraint**: If enabled, the object cannot rotate.
		* 
		* These constraints allow you to restrict movement for specific scenarios (e.g., a platform that shouldn't move
		* or a character that should only move horizontally).
		*/
		PhysicsConstraints constraints;

		/**
		* \brief Elasticity factor of the material (bounce factor).
		*
		* The `elasticity_coefficient` controls how much of the object's velocity is retained after a collision.
		* It represents the material's ability to bounce or recover velocity upon impact. The coefficient is a value
		* between 0.0 and 1.0, where:
		*
		* - **0.0** means no velocity is retained after the collision (all velocity is lost, and the object does not bounce).
		* - **1.0** means the object retains its full velocity but in the opposite direction (perfect elastic bounce).
		* - **0.5** means the object retains half of its velocity, resulting in a bounce with reduced speed.
		*
		* This factor can be used to simulate different materials, such as rubber (high elasticity) or concrete (low elasticity).
		*/
		float elastisity_coefficient = 0.0;

		/**
		* \brief Offset of all colliders relative to the object's transform position.
		*
		* The `offset` defines a positional shift applied to all colliders associated with the object, relative to the object's
		* transform position. This allows for the colliders to be placed at a different position than the object's actual
		* position, without modifying the object's transform itself.
		* 
		* - The `offset` is typically used to adjust the collider's position in cases where all colluders should be moved.
		* - For example, if a character has a animation where all colliders should be moved this offset can be used to 
		*		achieve this.
		*/
		vec2 offset;
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
