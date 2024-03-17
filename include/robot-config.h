#pragma once
#include <vex.h>


// VEXcode devices
extern vex::brain Brain;
extern vex::controller Controller1;
extern vex::motor frontLeftWheel;
extern vex::motor frontRightWheel;
extern vex::motor backLeftWheel;
extern vex::motor backRightWheel;
extern vex::encoder leftEncoder;
extern vex::encoder rightEncoder;
extern vex::encoder backEncoder;
extern vex::inertial inertialSensor;
extern vex::gps gps;


extern vex::competition Competition;

void vexcodeInit();