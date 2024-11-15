#pragma once

#include <cstdint>

#include "../Component.h"

#include "Vector2.h"

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
		//! X constraint
		bool x = false;
		//! Y constraint
		bool y = false;
		//! rotation constraint
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
		double mass = 0.0;
		//! gravtiy scale
		double gravity_scale = 0.0;
		//! Changes if physics apply
		BodyType body_type = BodyType::DYNAMIC;
		//! linear velocity of object
		Vector2 linear_velocity;
		//! maximum linear velocity of object
		Vector2 max_linear_velocity;
		//! linear damping of object
		Vector2 linear_damping;
		//! angular velocity of object
		double angular_velocity = 0.0;
		//! max angular velocity of object
		double max_angular_velocity = 0.0;
		//! angular damping of object
		double angular_damping = 0.0;
		//! movements constraints of object
		PhysicsConstraints constraints;
		//! if gravity applies
		bool use_gravity = true;
		//! if object bounces
		bool bounce = false;
	};

public:
	/** 
	 * \param game_object_id id of the gameobject the rigibody is added to.
	 * \param data struct to configure the rigidbody.
	 */
	Rigidbody(uint32_t game_object_id, const Data & data);
	//! struct to hold data of rigidbody
	Data data;

public:
	/** 
	 * \brief add a linear force to the Rigidbody.
	 * 
	 * \param force Vector2 that is added to the linear force.
	 */
	void add_force_linear(const Vector2 & force);
	/** 
	 * \brief add a angular force to the Rigidbody.
	 * 
	 * \param force Vector2 that is added to the angular force.
	 */
	void add_force_angular(double force);
};

} // namespace crepe
