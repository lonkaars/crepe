#pragma once

#include <format>

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

	//! Truncates the vector to a maximum length.
	void truncate(T max);

	//! Normalizes the vector (resulting in vector with a length of 1).
	void normalize();

	//! Returns the length of the vector.
	T length() const;

	//! Returns the squared length of the vector.
	T length_squared() const;

	//! Returns the dot product (inwendig product) of this vector and another vector.
	T dot(const Vector2<T> & other) const;

	//! Returns the distance between this vector and another vector.
	T distance(const Vector2<T> & other) const;

	//! Returns the squared distance between this vector and another vector.
	T distance_squared(const Vector2<T> & other) const;

	//! Returns the perpendicular vector to this vector.
	Vector2 perpendicular() const;
};

} // namespace crepe

template <typename T>
struct std::formatter<crepe::Vector2<T>> : std::formatter<std::string> {
	format_context::iterator format(crepe::Vector2<T> vec, format_context & ctx) const;
};

#include "Vector2.hpp"
