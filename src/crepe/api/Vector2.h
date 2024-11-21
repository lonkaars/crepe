#pragma once

namespace crepe {

//! 2D vector
template <class T>
struct Vector2 {
	//! X component of the vector
	T x = 0;
	//! Y component of the vector
	T y = 0;

	//! Subtracts another vector from this vector and returns the result.
	Vector2 operator-(const Vector2 & other) const;

	//! Adds another vector to this vector and returns the result.
	Vector2 operator+(const Vector2 & other) const;

	//! Multiplies this vector by a scalar and returns the result.
	Vector2 operator*(double scalar) const;

	//! Multiplies this vector by another vector element-wise and updates this vector.
	Vector2 & operator*=(const Vector2 & other);

	//! Adds another vector to this vector and updates this vector.
	Vector2 & operator+=(const Vector2 & other);

	//! Adds a scalar value to both components of this vector and updates this vector.
	Vector2 & operator+=(double other);

	//! Returns the negation of this vector.
	Vector2 operator-() const;

	//! Checks if this vector is equal to another vector.
	bool operator==(const Vector2 & other) const;

	//! Checks if this vector is not equal to another vector.
	bool operator!=(const Vector2 & other) const;
};

} // namespace crepe

#include "Vector2.hpp"
