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
	struct physics_constraints {
		//! X constraint
		bool x; 
		//! Y constraint
		bool y; 
		//! rotation constraint
		bool rotation; 
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
	double mass;
	double gravity_scale;
	BodyType body_type;
	Vector2 linear_velocity;
	Vector2 max_linear_velocity;
	Vector2 linear_damping;
	double angular_velocity;
	double max_angular_velocity;
	double angular_damping;
	physics_constraints constraints;
	bool use_gravity;
	bool bounce;
};

} // namespace crepe
