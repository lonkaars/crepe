#pragma once
#include <cmath>
struct Vector2 {
    float x; // X component of the vector
    float y; // Y component of the vector

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
struct Collision {
    int objectIdA;          // ID of the first object
    int objectIdB;          // ID of the second object
    Vector2 contactPoint;   // Point of contact
    Vector2 contactNormal;  // Normal vector at the contact point

    // Constructor to initialize a Collision
    Collision(int idA, int idB, const Vector2& point, const Vector2& normal, float depth)
        : objectIdA(idA), objectIdB(idB), contactPoint(point), contactNormal(normal) {}

};
