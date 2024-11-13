#include "Vector2.h"

using namespace crepe;

Vector2 Vector2::operator-(const Vector2 & other) const {
	return {x - other.x, y - other.y};
}

Vector2 Vector2::operator+(const Vector2 & other) const {
	return {x + other.x, y + other.y};
}

Vector2 Vector2::operator*(float scalar) const {
	return {x * scalar, y * scalar};
}

Vector2 & Vector2::operator*=(const Vector2 & other) {
	x *= other.x;
	y *= other.y;
	return *this;
}

Vector2 & Vector2::operator+=(const Vector2 & other) {
	x += other.x;
	y += other.y;
	return *this;
}

Vector2 & Vector2::operator+=(float other) {
	x += other;
	y += other;
	return *this;
}

Vector2 Vector2::operator-() const { return {-x, -y}; }

bool Vector2::operator==(const Vector2 & other) const {
	return x == other.x && y == other.y;
}

bool Vector2::operator!=(const Vector2 & other) const {
	return !(*this == other);
}

