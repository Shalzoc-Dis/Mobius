#pragma once

#include <vex.h>
#include <vector>
#include "Profiler.h"
#include <random>
#include <array>
//#include "Bezier.h"

namespace Mobius {


enum class rotationUnits {
    rad, deg, rev
};

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

        // Returns the angle between a line pointing to the point from the origin and the x-axis. This is counter-clockwise and in radians
        float angle() {
            float polar = polarAngle();
            if (polar < 0) {
                polar += M_TWOPI;
            }
            return polar;
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
        vector2 rotated(float angle) {
            // Reference: https://matthew-brett.github.io/teaching/rotation_2d.html
            vector2 res(0, 0);
            res.x = (cos(angle) * x) - (sin(angle) * y);
            res.y = (sin(angle) * x) + (cos(angle) * y); 
            return res;
        }


        // @brief Rotate the vector counter-clockwise by a given angle
        // @param angle The angle in radians
        void rotate(float angle) {
            // Reference: https://matthew-brett.github.io/teaching/rotation_2d.html
            //if (this->x != 0.0f && this->y != 0.0f) {
                x = (cos(angle) * x) - (sin(angle) * y);
                y = (sin(angle) * x) + (cos(angle) * y); 
                printf("Rotation applied (%f)\n", angle);
            //}
        }


        // @brief Calculate the dot product of two vectors
        // @param obj The other vector
        float dot(vector2 obj) {
            return x * obj.x + y * obj.y;
        }

    }; // struct vector2

// A struct to represent a position on a field made up of a 2D vector and an angle
struct Position {
    float x, y; // In cm
    float angle;   // In radians

    // @param position The position of the robot as a 2D vector
    // @param angle The angle of the robot in radians
    Position(Mobius::vector2 position, float angle)
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



} // namespace Mobius