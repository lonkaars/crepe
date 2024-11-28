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
	Vector2 operator-(const Vector2<T> & other) const;

	//! Subtracts a scalar value from both components of this vector and returns the result.
	Vector2 operator-(T scalar) const;

	//! Adds another vector to this vector and returns the result.
	Vector2 operator+(const Vector2<T> & other) const;

	//! Adds a scalar value to both components of this vector and returns the result.
	Vector2 operator+(T scalar) const;

	//! Multiplies this vector by another vector element-wise and returns the result.
	Vector2 operator*(const Vector2<T> & other) const;

	//! Multiplies this vector by a scalar and returns the result.
	Vector2 operator*(T scalar) const;

	//! Divides this vector by another vector element-wise and returns the result.
	Vector2 operator/(const Vector2<T> & other) const;

	//! Divides this vector by a scalar and returns the result.
	Vector2 operator/(T scalar) const;

	//! Adds another vector to this vector and updates this vector.
	Vector2 & operator+=(const Vector2<T> & other);

	//! Adds a scalar value to both components of this vector and updates this vector.
	Vector2 & operator+=(T other);

	//! Subtracts another vector from this vector and updates this vector.
	Vector2 & operator-=(const Vector2<T> & other);

	//! Subtracts a scalar value from both components of this vector and updates this vector.
	Vector2 & operator-=(T other);

	//! Multiplies this vector by another vector element-wise and updates this vector.
	Vector2 & operator*=(const Vector2<T> & other);

	//! Multiplies this vector by a scalar and updates this vector.
	Vector2 & operator*=(T other);

	//! Divides this vector by another vector element-wise and updates this vector.
	Vector2 & operator/=(const Vector2<T> & other);

	//! Divides this vector by a scalar and updates this vector.
	Vector2 & operator/=(T other);

	//! Returns the negation of this vector.
	Vector2 operator-() const;

	//! Checks if this vector is equal to another vector.
	bool operator==(const Vector2<T> & other) const;

	//! Checks if this vector is not equal to another vector.
	bool operator!=(const Vector2<T> & other) const;
};

} // namespace crepe

#include "Vector2.hpp"
