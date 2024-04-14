#pragma once
#include <vex.h>
#include "Field.h"


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

// The motor for the intake roller
extern vex::motor intakeMotor;

// The robot's GPS (Game Positioning System) sensor. This works by optically tracking the robot's position on the field
extern vex::gps gps;

extern Mobius::Field field;


extern vex::competition Competition;

void vexcodeInit();