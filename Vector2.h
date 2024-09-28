#pragma once

#include <cmath>

struct Vector2 {
    float x, y;

    Vector2(float x, float y) : x(x), y(y) {}

    // Euclidean distance
    float getDistance(const Vector2& other) const {
        float dx = x - other.x;
        float dy = y - other.y;
        return sqrt(dx * dx + dy * dy);
    }

    // addition
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    // subtraction
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    // dot product
    Vector2 operator*(const Vector2& other) const {
        return Vector2(x * other.x, y * other.y);
    }

    // scalar multiplication
    Vector2 operator*(const float v) const {
        return Vector2(x * v, y * v);
    }

    // division
    Vector2 operator/(const float v) const {
        return Vector2(x / v, y / v);
    }

    // addition assignment
    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    // subtraction assignment
    Vector2& operator-=(const Vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    // dot product assignment
    Vector2& operator*=(const Vector2& other) {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    // scalar multiplication assignment
    Vector2& operator*=(const float v) {
        x *= v;
        y *= v;
        return *this;
    }

    // division assignment
    Vector2& operator/=(const float v) {
        x /= v;
        y /= v;
        return *this;
    }
};