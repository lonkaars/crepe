#pragma once

#include <cstdint>

#include "api/Point.h"

#include "Component.h"
#include <cstdint>
#include <cmath>

namespace crepe {

//! Vector2 struct
struct Vector2 {
		//! X component of the vector
		float x; 
		//! Y component of the vector
		float y;

		//! Subtracts another vector from this vector and returns the result.
		Vector2 operator-(const Vector2& other) const {
				return {x - other.x, y - other.y};
		}

		//! Adds another vector to this vector and returns the result.
		Vector2 operator+(const Vector2& other) const {
				return {x + other.x, y + other.y};
		}

		//! Multiplies this vector by a scalar and returns the result.
		Vector2 operator*(float scalar) const {
				return {x * scalar, y * scalar};
		}

		//! Multiplies this vector by another vector element-wise and updates this vector.
		Vector2& operator*=(const Vector2& other) {
				x *= other.x;
				y *= other.y;
				return *this;
		}

		//! Adds another vector to this vector and updates this vector.
		Vector2& operator+=(const Vector2& other) {
				x += other.x;
				y += other.y;
				return *this;
		}

		//! Adds a scalar value to both components of this vector and updates this vector.
		Vector2& operator+=(const double& other) {
				x += other;
				y += other;
				return *this;
		}

		//! Normalizes this vector and returns the result.
		Vector2 normalize() const {
				float length = std::sqrt(x * x + y * y);
				if (length == 0) return {0, 0}; // Prevent division by zero
				return {x / length, y / length};
		}

		//! Compares this vector's magnitude with another vector's magnitude.
		bool operator<(const Vector2& other) const {
				return this->magnitude() < other.magnitude();
		}

		//! Compares this vector's magnitude with another vector's magnitude.
		bool operator>(const Vector2& other) const {
				return this->magnitude() > other.magnitude();
		}

		//! Returns the negation of this vector.
		Vector2 operator-() const {
				return {-x, -y};
		}

		//! Checks if this vector is equal to another vector.
		bool operator==(const Vector2& other) const {
				return x == other.x && y == other.y;
		}

		//! Checks if this vector is not equal to another vector.
		bool operator!=(const Vector2& other) const {
				return !(*this == other);
		}

		//! Returns the magnitude (length) of this vector.
		float magnitude() const {
				return std::sqrt(x * x + y * y);
		}
};

class Transform : public Component {
	// FIXME: What's the difference between the `Point` and `Position`
	// classes/structs? How about we replace both with a universal `Vec2` that
	// works similar (or the same) as those found in GLSL?

public:
	Transform(uint32_t id, const Vector2& position, double rotation, double scale);
	~Transform();
	virtual int get_instances_max() const { return 1; }
	//! Translation (shift)
	Vector2 position = {0,0};
	//! Rotation, in radians
	double rotation = 0;
	//! Multiplication factor
	double scale = 0;	
};

} // namespace crepe
