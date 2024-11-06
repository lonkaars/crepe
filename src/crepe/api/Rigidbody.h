#pragma once

#include <cstdint>
#include "../Component.h"
#include "Transform.h"

namespace crepe {

/**
 * \brief Rigidbody class
 * 
 * This class is used by the physics sytem and collision system. 
 * It configures how to system interact with the gameobject for movement and collisions.
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
	 * This struct configures the movement constraint for this object.
	 * If a constraint is enabled the systems will not move the object.
	 */
	struct PhysicsConstraints {
		//! X constraint
		bool x = 0; 
		//! Y constraint
		bool y = 0; 
		//! rotation constraint
		bool rotation = 0; 
	};
public:
	/** 
	 * This struct holds the data for the Rigidbody.
	 */
	struct RigidbodyData{
		double mass = 0.0;
		double gravity_scale = 0.0;
		BodyType body_type = BodyType::DYNAMIC;
		Vector2 linear_velocity;
		Vector2 max_linear_velocity;
		Vector2 linear_damping;
		double angular_velocity = 0.0;
		double max_angular_velocity = 0.0;
		double angular_damping = 0.0;
		PhysicsConstraints constraints;
		bool use_gravity = true;
		bool bounce = false;
	};
public:
	/** 
	 * \param game_object_id id of the gameobject the rigibody is added to.
	 * \param data struct to configure the rigidbody.
	 */
	Rigidbody(uint32_t game_object_id,const RigidbodyData& data);
	//! struct to hold data of rigidbody
	RigidbodyData data;
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
