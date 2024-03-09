#pragma once

#include "MobiusUtilities.h"
#include "vex.h"

namespace Mobius {

    // ------------------------------------- Global constant information -----------------------------------------------------
namespace Robot {
    // Internal Information
    extern Position FieldCentricPosition;
    // Velocity and Acceleration
    extern vector2 velocity;    // In cm/s
    extern float angularVelocity; // In radians/s
    extern vector2 acceleration; // In cm/s^2
    extern float angularAcceleration; // In radians/s^2
    // TODO: maxVelocityInDirection and maxAngularVelocity
    extern float maxVelocityInDirection(float angle); // In cm/s
    extern float maxAngularVelocity(vector2 velocity);  // In radians/s

    // Physical Characteristics
    const float mass = 5;   // In kg
    const float wheelRadius = 10.16; // In cm
    const float odoWheelDiameter = 6.9; // In cm
    extern float width, length, height; // In cm
    // Wheel Positions
    const vector2 frontLeftWheelPosition;
    const vector2 frontRightWheelPosition;
    const vector2 backLeftWheelPosition;
    const vector2 backRightWheelPosition;
    const vector2 leftEncoderPosition;
    const vector2 rightEncoderPosition;
    const vector2 backEncoderPosition; 
    // This is the bias of the mecanum wheels. The more powerful direction is the lower number, which acts as a multiplier 
    // for the motor movements in that direction in order to make the robot move perfectly. This accounts for the friction in 
    // the wheels that our calculation does not account for.
    extern const float xBias;
    extern const float yBias;

    // State
    extern bool isAutonomous, isMoving, isDriverControlled;
    extern vector2 desiredVelcity;
    extern float desiredAngularVelocity;

    // Timers

         
} // namespace Robot

// Essential functionality
int RobotOdometry();
int MotionCalculator();



} // namespace Mobius