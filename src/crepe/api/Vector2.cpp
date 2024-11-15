#include "Vector2.h"

namespace crepe {

// Constructor with initial values
Vector2::Vector2(double x, double y) : x(x), y(y) {}

// Subtracts another vector from this vector and returns the result.
Vector2 Vector2::operator-(const Vector2 & other) const { return {x - other.x, y - other.y}; }

// Adds another vector to this vector and returns the result.
Vector2 Vector2::operator+(const Vector2 & other) const { return {x + other.x, y + other.y}; }

// Multiplies this vector by a scalar and returns the result.
Vector2 Vector2::operator*(double scalar) const { return {x * scalar, y * scalar}; }

// Multiplies this vector by another vector element-wise and updates this vector.
Vector2 & Vector2::operator*=(const Vector2 & other) {
	x *= other.x;
	y *= other.y;
	return *this;
}

// Adds another vector to this vector and updates this vector.
Vector2 & Vector2::operator+=(const Vector2 & other) {
	x += other.x;
	y += other.y;
	return *this;
}

// Adds a scalar value to both components of this vector and updates this vector.
Vector2 & Vector2::operator+=(double other) {
	x += other;
	y += other;
	return *this;
}

// Returns the negation of this vector.
Vector2 Vector2::operator-() const { return {-x, -y}; }

// Checks if this vector is equal to another vector.
bool Vector2::operator==(const Vector2 & other) const { return x == other.x && y == other.y; }

// Checks if this vector is not equal to another vector.
bool Vector2::operator!=(const Vector2 & other) const { return !(*this == other); }

} // namespace crepe
