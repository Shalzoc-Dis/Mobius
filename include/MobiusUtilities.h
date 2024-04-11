#pragma once

#include <vex.h>
#include <vector>
#include "Profiler.h"
#include <random>
#include <array>
//#include "Bezier.h"

namespace Mobius {

// A struct to represent a 2D vector
struct vector2 {

        vector2(float x, float y)
        : x(x), y(y) {}

        vector2() {}
        ~vector2() {}

        float x;
        float y;

        // This overloads the data type to allow for vector addition.
        vector2 operator+(vector2 const &obj) {
            vector2 res;
            res.x = x + obj.x;
            res.y = y + obj.y;
            return res;
        }

        // This overloads the data type to allow for vector subtraction.
        vector2 operator-(vector2 const &obj) {
            vector2 res;
            res.x = x - obj.x;
            res.y = y - obj.y;
            return res;
        }

        // @return The length of the hypotenuse AKA the vector's magnitude
        float magnitude() {
            return sqrt(pow(x, 2) + pow(y, 2));
        }

        // Returns the angle between a line pointing to the point from the origin and the x-axis
        float polarAngle() {
            return atan2(y, x); // Returns the angle in radians
        }

        // This overloads the data type to allow for scalar multiplication.
        vector2 operator*(float const &obj) {
            vector2 res;
            res.x = x * obj;
            res.y = y * obj;
            return res;
        }

        // This overloads the data type to allow for scalar multiplication.
        vector2 operator*=(float const &obj) {
            return vector2(x * obj, y * obj);
        }

        // This overloads the data type to allow for scalar division.
        vector2 operator/(float const &obj) {
            vector2 res;
            res.x = x / obj;
            res.y = y / obj;
            return res;
        }

        // This overloads the data type to allow for scalar division.
        vector2 operator/=(float const &obj) {
            return vector2(x / obj, y / obj);
        }

        // Normalise the vector. This proportionally scales the vector's components so that the magnitude is 1
        void normalise() {
            x /= magnitude();
            y /= magnitude();
        }

        // @return A normalised version of the vector. This proportionally scales the vector's components so that the magnitude is 1
        vector2 normalised() {
            vector2 res;
            res.x = x / magnitude();
            res.y = y / magnitude();
            return res;
        }

        // @brief Rotate the vector counter-clockwise by a given angle
        // @param angle The angle in radians
        vector2 rotate(float angle) {
            // Reference: https://matthew-brett.github.io/teaching/rotation_2d.html
            vector2 res;
            res.x = x * cos(angle) - y * sin(angle);
            res.y = x * sin(angle) + y * cos(angle); 
            return res;
        }
    }; // struct vector2

// A struct to represent a position on a field made up of a 2D vector and an angle
struct Position {
    float x, y; // In cm
    float angle;   // In radians

    // @param position The position of the robot as a 2D vector
    // @param angle The angle of the robot in radians
    Position(vector2 position, float angle)
     : x(position.x), y(position.y), angle(angle) {}

    // @param x The x coordinate of the robot
    // @param y The y coordinate of the robot
    // @param angle The angle of the robot in radians
    Position(float x, float y, float angle)
     : x(x), y(y), angle(angle) {}
    
    Position();
    ~Position() {};

    // This overloads the data type to allow for position addition. The components of the position are simply added together
    Position operator+(Position const &obj) {
        Position res;
        res.x = x + obj.x;
        res.y = y + obj.y;
        res.angle = angle + obj.angle;
        return res;
    }

    // This overloads the data type to allow for position subtraction. The components of the position are simply added together
    Position operator-(Position const &obj) {
        Position res;
        res.x = x - obj.x;
        res.y = y - obj.y;
        res.angle = angle - obj.angle;
        return res;
    }
};

// This is a struct to represent a point on a path which specifies a position and a rotation the robot should have at that point

// This is to contain a path. Each note on the path has a position and a rotation
struct CubicBezier;
struct Path {
    std::vector<Position> m_points;

    Path() {};
    ~Path() {};

    // @brief Draws the path on the Brain's Screen
    void visualise();

    // @brief returns the length of the path in cm
    float length();
    // @return the number of curves in the path
    uint8_t numCurves();

    // @brief Returns a reference to the nth curve in the path
    // @param n The index of the curve, starting at 0
    Mobius::CubicBezier& getNthCurve(uint8_t n) {};

};

} // namespace Mobius