#include "robot-config.h"


// vex::motor M_FL = vex::motor(vex::PORT1, vex::gearSetting::ratio18_1, bool reversed);
vex::motor frontLeftWheel = vex::motor(vex::PORT20, vex::ratio18_1, false);
vex::motor frontRightWheel = vex::motor(vex::PORT19, vex::ratio18_1, true);
vex::motor backLeftWheel = vex::motor(vex::PORT10, vex::ratio18_1, false);
vex::motor backRightWheel = vex::motor(vex::PORT9, vex::ratio18_1, true);


vex::encoder leftEncoder = vex::encoder(Brain.ThreeWirePort.C); // Top wire is in port C, the bottom is in port D
vex::encoder rightEncoder = vex::encoder(Brain.ThreeWirePort.A);  // Top wire is in port B, the bottom is in port A

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
}