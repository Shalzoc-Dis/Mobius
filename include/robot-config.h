#pragma once
#include <vex.h>


// VEXcode devices
// The robot's brain
extern vex::brain Brain;
// The robot's primary controller
extern vex::controller Controller1;
// The motor of the front left mecanum wheel
extern vex::motor frontLeftWheel;
// The motor of the front right mecanum wheel
extern vex::motor frontRightWheel;
// The motor of the back left mecanum wheel
extern vex::motor backLeftWheel;
// The motor of the back right mecanum wheel
extern vex::motor backRightWheel;

// The left odometry encoder
extern vex::encoder leftEncoder;
// The right odometry encoder
extern vex::encoder rightEncoder;
// The back odometry encoder
extern vex::encoder backEncoder;

// The inertial sensor
extern vex::inertial inertialSensor;
// The robot's GPS (Game Positioning System) sensor. This works by optically tracking the robot's position on the field
extern vex::gps gps;


extern vex::competition Competition;

void vexcodeInit();