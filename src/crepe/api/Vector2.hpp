#pragma once

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

} // namespace crepe
