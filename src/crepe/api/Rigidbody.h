#pragma once

#include <cstdint>
#include <cmath>
#include "../Component.h"

namespace crepe::api {

// FIXME: can't this enum be defined inside the class declaration of Rigidbody?
enum class BodyType {
	//! Does not move (e.g. walls, ground ...)
	STATIC,
	//! Moves and responds to forces (e.g. player, physics objects ...)
	DYNAMIC,
	//! Moves but does not respond to forces (e.g. moving platforms ...)
	KINEMATIC,
};

struct Vector2 {
    float x = 0; // X component of the vector
    float y = 0; // Y component of the vector

    // Vector subtraction
    Vector2 operator-(const Vector2& other) const {
        return {x - other.x, y - other.y};
    }

    // Vector addition
    Vector2 operator+(const Vector2& other) const {
        return {x + other.x, y + other.y};
    }

    // Scalar multiplication
    Vector2 operator*(float scalar) const {
        return {x * scalar, y * scalar};
    }

    // Normalize the vector
    Vector2 normalize() const {
        float length = std::sqrt(x * x + y * y);
        if (length == 0) return {0, 0}; // Prevent division by zero
        return {x / length, y / length};
    }
};

class Rigidbody : public Component {
public:
	Rigidbody(uint32_t game_object_id, double mass, double gravity_scale,
			  BodyType body_type);
	Vector2 velocity;
	double mass;
	double gravity_scale;
	BodyType body_type;
};

} // namespace crepe::api
