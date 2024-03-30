#include "robot-config.h"


// vex::motor M_FL = vex::motor(vex::PORT1, vex::gearSetting::ratio18_1, bool reversed);
vex::motor frontLeftWheel = vex::motor(vex::PORT14, vex::ratio18_1, false);
vex::motor frontRightWheel = vex::motor(vex::PORT17, vex::ratio18_1, true);
vex::motor backLeftWheel = vex::motor(vex::PORT13, vex::ratio18_1, false);
vex::motor backRightWheel = vex::motor(vex::PORT16, vex::ratio18_1, true);


vex::encoder leftEncoder = vex::encoder(Brain.ThreeWirePort.C); // Top wire is in port C, the bottom is in port D
vex::encoder rightEncoder = vex::encoder(Brain.ThreeWirePort.A);  // Top wire is in port B, the bottom is in port A
vex::encoder backEncoder = vex::encoder(Brain.ThreeWirePort.E);

vex::inertial inertialSensor = vex::inertial(vex::PORT1);
vex::gps gps = vex::gps(vex::PORT2, 0, 0, vex::distanceUnits::mm, 0);

vex::controller Controller1 = vex::controller(vex::controllerType::primary);



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit() {
  printf("Initialising...\n");
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // Reset the Encoders
  Brain.Screen.print("Resetting Encoders...");
  Brain.Screen.setCursor(3, 1);
  leftEncoder.resetRotation();
  rightEncoder.resetRotation();
  backEncoder.resetRotation();
  // Calibrate the GPS
  if (gps.installed()) {
    Brain.Screen.print("Initialising GPS...");
    Brain.Screen.setCursor(4, 1);
    gps.calibrate();
    waitUntil(!gps.isCalibrating());
  }
}