#pragma once
#include <cmath>

class Vector2 {
public:
    float x;
    float y;

    Vector2() : x(0), y(0) {}
    Vector2(float _x, float _y) {
        x = _x;
        y = _y;
    }
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    Vector2 operator/(float scalar) const {
        return Vector2(x / scalar, y / scalar);
    }

    float Magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    Vector2 Normalized() const {
        float magnitude = Magnitude();

        if (magnitude == 0) {
            return Vector2(0, 0);
        }
        else {
            return Vector2(x / magnitude, y / magnitude);
        }
    }
};
class Vector2int {
public:
    int x;
    int y;

    Vector2int() : x(0), y(0) {}
    Vector2int(int _x, int _y) : x(_x), y(_y) {}

    Vector2int operator+(const Vector2int& other) const {
        return Vector2int(x + other.x, y + other.y);
    }
};