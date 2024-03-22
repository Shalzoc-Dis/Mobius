#include "Robot.h"

float Mobius::Robot::maxVelocityInDirection(float angle) {
    //                               2πr * rev/min * 60min/s * mysteryConstant
    const float maxForwardVelocity = Robot::wheelRadius * M_TWOPI * 200 * 60 * 1.0f;
    const float maxSidewaysVelocity = 1;
    return 1.0f;
};

float Mobius::Robot::maxAngularVelocity(vector2 velocity) {
    return 1.0f;
};