#pragma once

#include "MobiusUtilities.h"
#include "robot-config.h"
#include "vex.h"
#include "Bezier.h"
#include "Field.h"

extern vex::competition Competition;
extern vex::brain Brain;
namespace Mobius {

    // ------------------------------------- Global constant information -----------------------------------------------------
namespace Robot {
    extern vex::controller Controller1;
    extern Mobius::Field field;

    
    // Internal Information
    // Position of the Robot according to the field. 0, 0 is in the middle of the field
    extern Position FieldCentricPosition;

    // This is to adjust for the position of the GPS strips. This enum stats where 0 degrees is
    // This is also used to determind where the drivers are standing
    enum class fieldSide { RED_GOAL, BLUE_GOAL, BLUE_BAR, RED_BAR };

    // The position on the field the robot wants to be at
    extern Position desiredPosition;
    // The angle between the front of the robot and a line between it and the desired position
    extern float driveAngle;
    // The maximum speed the robot can go
    extern float driveSpeed;

    extern vector2 velocity;            // In cm/s
    extern float angularVelocity;       // In radians/s
    extern vector2 acceleration;        // In cm/s^2
    extern float angularAcceleration;   // In radians/s^2 
    extern vector2 momentum;            // In kg * m/s

    // Physical Characteristics
    const float mass = 5;   // In kg
    const float wheelRadius = 5.08; // In cm
    // This is the offset from the centre of the robot to the wheels. x right, y is forwards. In cm
    const vector2 wheelOffset(16.8f, 18.0f);
    extern float width, length, height; // Robot's dimensions in cm

    // Odometry 
    const float odoWheelRadius = 3.45; // In cm
    // This is the offset from the centre of the robot to the left odometry wheel. x right, y is forwards. In cm
    const vector2 leftEncoderPosition(-3, 4);
    // This is the offset from the centre of the robot to the right odometry wheel. x right, y is forwards. In cm
    const vector2 rightEncoderPosition(3, 4);
    // This is the offset from the centre of the robot to the back odometry wheel. x right, y is forwards. In cm
    const vector2 backEncoderPosition(0, -3); 

    // This is the offset from the centre of the robot to the GPS sensor.
    // @param x distance to the right
    // @param y distance forwards
    // @param angle angle from the front of the robot
    extern Position gpsOffset;

    // This is the bias of the mecanum wheels. The more powerful direction is the lower number, which acts as a multiplier 
    // for the motor movements in that direction in order to make the robot move perfectly. This accounts for the friction in 
    // the wheels that our calculation does not account for.
    /*
    const float xBias = 1.0f;
    const float yBias = 1.0f;
    */

    // Enum for the current control state of the robot
    enum class state { AUTONOMOUS, DRIVER_CONTROLLED, DISABLED };
    enum class controlMode { FIELD_CENTRIC, ROBOT_CENTRIC };
    // The current control state of the robot
    extern state controlState;
    extern controlMode currentControlMode;

    // TODO: Enum for the current type of match
    enum class matchType { SKILLS, HEAD_TO_HEAD, AUTONOMOUS_SKILLS};
    // The current match type the robot is playing
    extern matchType currentMatchType;

    extern bool inCompetition;

    // Weather the robot can use a gps or not
    extern bool gpsAvailable;

    // The desired velocity of the robot in cm/s
    extern vector2 desiredVelocity;
    // The desired angular velocity of the robot in radians/s
    extern float desiredAngularVelocity;

    // Competition field information

    // Drivers POV
    extern fieldSide driverSide;
    extern fieldSide GPS_0_Degree;

    // Timers
    // Timer to calculate the delta time for the positioning computer
    extern vex::timer PositioningComputerUpdateTimer;
    // Timer for the current control period
    extern vex::timer controlPeriodTimer;


    // Listens to the control state of the robot and calculates how it needs to move to either follow a path or the controller
    void MotionCalculators();
    // Calculates the robot's position, velocity, and acceleration
    int PositioningComputer();
    // Update the manipulators
    void ManipulatorControl();
    // Create callbacks for controller actions
    void ControllerCallbacks();

    // Give the user feedback
    int ControllerHUD();


    // Functions for competition
    void autonomous();
    void teleOp();
    void init();
   
} // namespace Robot


// Essential functionality
int RobotOdometry();







} // namespace Mobius