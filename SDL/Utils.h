#pragma once
#include <cmath>

class Vector2 {
public:
    float x;
    float y;

    //Vector2 uses float, convenient for positions directions and speed 
    //Vector2int is used for sizes and grid positions (for example, taking the projectile asset from the .png)

    //Constructors with default value of 0 to not start moving 
    Vector2() : x(0), y(0) {}
    //Allows me to assign specific values
    Vector2(float _x, float _y) {
        x = _x;
        y = _y;
    }
    //The following operators allow me to make mathematical equations with the Vector2
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

    //Calculates the length of the vector2
    float Magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    Vector2 Normalized() const {
        //Allows us to only work with pure direction and mantain a consistent movement speed 
        float magnitude = Magnitude();

        if (magnitude == 0) {
            return Vector2(0, 0);
        }
        else {
            return Vector2(x / magnitude, y / magnitude);
        }
    }
};
//Takes the same use as the previous one just in integers
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