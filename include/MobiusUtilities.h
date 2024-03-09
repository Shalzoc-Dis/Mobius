#pragma once

#include <vex.h>

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
            vector2 res;
            // Alpha is the current angle of the vector
            float alpha = polarAngle();
            float hyp = magnetude();
            // Make sure the angle is between 0 and 2PI
            do {
            angle > 2 * M_PI ? angle -= 2 * M_PI : angle;
            } while (angle > 2 * M_PI);
            // Beta is the final angle of the vector
            float beta = alpha + angle;
            res.x = hyp * cos(beta);
            res.y = hyp * sin(beta);
            return res;
        }
    }; // struct vector2

struct Position {
    float x, y;
    float angle;    // Radians

    Position(vector2 position, float angle);
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