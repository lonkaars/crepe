#pragma once

#include <cstdint>
#include "../Component.h"
#include "Transform.h"

namespace crepe::api {

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
	struct physics_constraints {
		//! X constraint
		bool x = 0; 
		//! Y constraint
		bool y = 0; 
		//! rotation constraint
		bool rotation = 0; 
	};

public:
	Rigidbody(
		uint32_t game_object_id, 
		double mass, 
		double gravity_scale,
		BodyType body_type,
		const Vector2& linear_velocity,
		const Vector2& max_linear_velocity,
		const Vector2& linear_damping,
		double angular_velocity,
		double max_angular_velocity,
		double angular_damping,
		physics_constraints constraints,
		bool use_gravity,
		bool bounce
		);
	double mass =0;
	double gravity_scale=0;
	BodyType body_type = BodyType::STATIC;
	Vector2 linear_velocity = {0,0};
	Vector2 max_linear_velocity = {0,0};
	Vector2 linear_damping= {0,0};
	double angular_velocity = 0;
	double max_angular_velocity = 0;
	double angular_damping = 0;
	physics_constraints constraints = {0,0,0};
	bool use_gravity = 0;
	bool bounce = 0;
};

} // namespace crepe::api
