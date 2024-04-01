#include "Robot.h"


Mobius::Field field;

float Mobius::Robot::maxVelocityInDirection(float angle) {
    //                               2πr * rev/min * 60min/s * mysteryConstant
    const float maxForwardVelocity = Robot::wheelRadius * M_TWOPI * 200 * 60 * 1.0f;
    const float maxSidewaysVelocity = 1;
    return 1.0f;
};

float Mobius::Robot::maxAngularVelocity(vector2 velocity) {
    return 1.0f;
};


namespace Mobius { namespace Robot {
// Implementations of the vaiables in Robot.h
Position FieldCentricPosition(0, 0, 0);
Position desiredPosition(0, 0, 0);
float driveAngle;
float driveSpeed;
// Velocity and Acceleration
vector2 velocity;    // In cm/s
float angularVelocity; // In radians/s
vector2 acceleration; // In cm/s^2
float angularAcceleration; // In radians/s^2
vector2 momentum;

// Physical Characteristics
float width, length, height; // In cm

// State
state controlState;
matchType currentMatchType;
vector2 desiredVelocity;
float desiredAngularVelocity;



} // namespace Mobius::Robot   
} // namespace Mobius