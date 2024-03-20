#pragma once
#include "Robot.h"

float Mobius::Robot::maxVelocityInDirection(float angle) {
    const float maxForwardVelocity = 1;
    const float maxSidewaysVelocity = 1;
    return 1.0f;
};

float Mobius::Robot::maxAngularVelocity(vector2 velocity) {
    return 1.0f;
};