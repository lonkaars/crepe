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
		float mass = 0.0;
		//! gravtiy scale
		float gravity_scale = 0;
		//! Changes if physics apply
		BodyType body_type = BodyType::DYNAMIC;
		//! linear velocity of object
		vec2 linear_velocity;
		//! maximum linear velocity of object
		vec2 max_linear_velocity = {INFINITY ,INFINITY};
		//! linear damping of object
		vec2 linear_velocity_factor;
		//! angular velocity of object
		float angular_velocity = 1;
		//! max angular velocity of object
		float max_angular_velocity = INFINITY;
		//! angular damping of object
		float angular_velocity_factor = 1;
		//! movements constraints of object
		PhysicsConstraints constraints;
		//! bounce factor of material. 0.0 <= means all velocity is lost, 1.0 means it gets the same momentum but the mirrored direction. 0.5 is half of the velocity is saved.
		float elastisity = 0.0;
		//! offset of all colliders relative to transform position
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
};

} // namespace crepe
