#pragma once

#include <cstdint>
#include "../Component.h"
#include "Transform.h"

namespace crepe {

//! Rigidbody component
class Rigidbody : public Component {
public:
	enum class BodyType {
		//! Does not move (e.g. walls, ground ...)
		STATIC,
		//! Moves and responds to forces (e.g. player, physics objects ...)
		DYNAMIC,
		//! Moves but does not respond to forces (e.g. moving platforms ...)
		KINEMATIC,
	};
	struct PhysicsConstraints {
		//! X constraint
		bool x = 0; 
		//! Y constraint
		bool y = 0; 
		//! rotation constraint
		bool rotation = 0; 
	};
public:
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
	Rigidbody(uint32_t game_object_id,const RigidbodyData& data);
	RigidbodyData data;
public:
	void add_force_linear(const Vector2 & force);
	void add_force_angular(double force);
};

} // namespace crepe
