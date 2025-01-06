#pragma once

#include <cmath>

#include "Vector2.h"

namespace crepe {

template <class T>
Vector2<T> Vector2<T>::operator-(const Vector2<T> & other) const {
	return {x - other.x, y - other.y};
}

template <class T>
Vector2<T> Vector2<T>::operator-(T scalar) const {
	return {x - scalar, y - scalar};
}

template <class T>
Vector2<T> Vector2<T>::operator+(const Vector2<T> & other) const {
	return {x + other.x, y + other.y};
}

template <class T>
Vector2<T> Vector2<T>::operator+(T scalar) const {
	return {x + scalar, y + scalar};
}

template <class T>
Vector2<T> Vector2<T>::operator*(const Vector2<T> & other) const {
	return {x * other.x, y * other.y};
}

template <class T>
Vector2<T> Vector2<T>::operator*(T scalar) const {
	return {x * scalar, y * scalar};
}

template <class T>
Vector2<T> Vector2<T>::operator/(const Vector2<T> & other) const {
	return {x / other.x, y / other.y};
}

template <class T>
Vector2<T> Vector2<T>::operator/(T scalar) const {
	return {x / scalar, y / scalar};
}

template <class T>
Vector2<T> & Vector2<T>::operator+=(const Vector2<T> & other) {
	x += other.x;
	y += other.y;
	return *this;
}

template <class T>
Vector2<T> & Vector2<T>::operator+=(T other) {
	x += other;
	y += other;
	return *this;
}

template <class T>
Vector2<T> & Vector2<T>::operator-=(const Vector2<T> & other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

template <class T>
Vector2<T> & Vector2<T>::operator-=(T other) {
	x -= other;
	y -= other;
	return *this;
}

template <class T>
Vector2<T> & Vector2<T>::operator*=(const Vector2<T> & other) {
	x *= other.x;
	y *= other.y;
	return *this;
}

template <class T>
Vector2<T> & Vector2<T>::operator*=(T other) {
	x *= other;
	y *= other;
	return *this;
}

template <class T>
Vector2<T> & Vector2<T>::operator/=(const Vector2<T> & other) {
	x /= other.x;
	y /= other.y;
	return *this;
}

template <class T>
Vector2<T> & Vector2<T>::operator/=(T other) {
	x /= other;
	y /= other;
	return *this;
}

template <class T>
Vector2<T> Vector2<T>::operator-() const {
	return {-x, -y};
}

template <class T>
bool Vector2<T>::operator==(const Vector2<T> & other) const {
	return x == other.x && y == other.y;
}

template <class T>
bool Vector2<T>::operator!=(const Vector2<T> & other) const {
	return !(*this == other);
}

template <class T>
void Vector2<T>::truncate(T max) {
	if (length() > max) {
		normalize();
		*this *= max;
	}
}

template <class T>
void Vector2<T>::normalize() {
	T len = length();
	if (len > 0) {
		*this /= len;
	}
}

template <class T>
T Vector2<T>::length() const {
	return std::sqrt(x * x + y * y);
}

template <class T>
T Vector2<T>::length_squared() const {
	return x * x + y * y;
}

template <class T>
T Vector2<T>::dot(const Vector2<T> & other) const {
	return x * other.x + y * other.y;
}

template <class T>
T Vector2<T>::distance(const Vector2<T> & other) const {
	return (*this - other).length();
}

template <class T>
T Vector2<T>::distance_squared(const Vector2<T> & other) const {
	return (*this - other).length_squared();
}

template <class T>
Vector2<T> Vector2<T>::perpendicular() const {
	return {-y, x};
}

template <class T>
bool Vector2<T>::is_nan() const {
	return std::isnan(x) && std::isnan(y);
}

template <class T>
Vector2<T> Vector2<T>::rotate(float deg) const {
	float rad = -deg / 180 * M_PI;
	return {
		x * std::cos(rad) - y * std::sin(rad),
		x * std::sin(rad) + y * std::cos(rad),
	};
}


} // namespace crepe
