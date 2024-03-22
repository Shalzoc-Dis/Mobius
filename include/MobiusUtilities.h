#pragma once

#include <vex.h>
#include <vector>
#include "Profiler.h"

namespace Mobius {

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

        float magnetude() {
            return sqrt(pow(x, 2) + pow(y, 2));
        }

        float polarAngle() {
            return atan2(y, x); // Returns the angle in radians
        }

        vector2 operator*(float const &obj) {
            vector2 res;
            res.x = x * obj;
            res.y = y * obj;
            return res;
        }

        vector2 operator/(float const &obj) {
            vector2 res;
            res.x = x / obj;
            res.y = y / obj;
            return res;
        }

        void normalise() {
            x /= magnetude();
            y /= magnetude();
        }

        vector2 normalised() {
            vector2 res;
            res.x = x / magnetude();
            res.y = y / magnetude();
            return res;
        }

        // Rotate the vector by a given angle in radians
        vector2 rotate(float angle) {   // This angle is in positive radians. It specifies counter-clockwise rotation angle
            // Reference: https://matthew-brett.github.io/teaching/rotation_2d.html
            vector2 res;
            res.x = x * cos(angle) - y * sin(angle);
            res.y = x * sin(angle) + y * cos(angle); 
            return res;
        }
    }; // struct vector2

struct Position {
    float x, y;
    float angle;    // Radians

    Position(vector2 position, float angle)
     : x(position.x), y(position.y), angle(angle) {}
     Position(float x, float y, float angle)
      : x(x), y(y), angle(angle) {}
    
    Position();
    ~Position() {};

    Position operator+(Position const &obj) {
        Position res;
        res.x = x + obj.x;
        res.y = y + obj.y;
        res.angle = angle + obj.angle;
        return res;
    }

    Position operator-(Position const &obj) {
        Position res;
        res.x = x - obj.x;
        res.y = y - obj.y;
        res.angle = angle - obj.angle;
        return res;
    }
};

struct PathNode {
    Position position;
    vector2 incomingControlPoint;
    vector2 outgoingControlPoint;

    PathNode();
    PathNode(Position position, vector2 incomingControlPoint, vector2 outgoingControlPoint);
    ~PathNode();
};

} // namespace Mobius