#pragma once

#include "MobiusUtilities.h"
#include "robot-config.h"
#include "vex.h"
#include "Bezier.h"
#include "Field.h"

namespace Mobius {

    // ------------------------------------- Global constant information -----------------------------------------------------
namespace Robot {
    extern vex::brain Brain;
    // Internal Information
    extern Position FieldCentricPosition;
    extern Position desiredPosition;
    extern float driveAngle;
    extern float driveSpeed;
    // Velocity and Acceleration
    extern vector2 velocity;    // In cm/s
    extern float angularVelocity; // In radians/s
    extern vector2 acceleration; // In cm/s^2
    extern float angularAcceleration; // In radians/s^2
    extern vector2 momentum;
    // TODO: maxVelocityInDirection and maxAngularVelocity
    extern float maxVelocityInDirection(float angle); // In cm/s
    extern float maxAngularVelocity(vector2 velocity);  // In radians/s

    // Physical Characteristics
    const float mass = 5;   // In kg
    const float wheelRadius = 5.08; // In cm
    const vector2 wheelOffset(16.8f, 18.0f); // In cm
    extern float width, length, height; // In cm
    // Wheel Positions
    const float odoWheelDiameter = 6.9; // In cm
    const vector2 leftEncoderPosition(-3, 4);
    const vector2 rightEncoderPosition(3, 4);
    const vector2 backEncoderPosition(0, -3); 
    // Other
    const Position gpsOffset(0, 0, 0); // In mm

    // This is the bias of the mecanum wheels. The more powerful direction is the lower number, which acts as a multiplier 
    // for the motor movements in that direction in order to make the robot move perfectly. This accounts for the friction in 
    // the wheels that our calculation does not account for.
    const float xBias = 1.0f;
    const float yBias = 1.0f;


    // State
    enum class state { AUTONOMOUS, DRIVER_CONTROLLED };
    extern state controlState;
    extern vector2 desiredVelocity;
    extern float desiredAngularVelocity;

    // Field
    extern Field field;

    // Timers
    extern vex::timer PositioningComputerUpdateTimer;

         
void MotionCalculatorByVelocity();
void DirectionCalculator();
} // namespace Robot

// Essential functionality
int positioningComputer();
int RobotOdometry();





} // namespace Mobius