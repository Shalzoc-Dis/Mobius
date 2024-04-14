#include "robot-config.h"
#include "Robot.h"


vex::brain Brain;

// vex::motor M_FL = vex::motor(vex::PORT1, vex::gearSetting::ratio18_1, bool reversed);
vex::motor frontLeftWheel = vex::motor(vex::PORT11, vex::ratio18_1, false);
vex::motor frontRightWheel = vex::motor(vex::PORT20, vex::ratio18_1, true);
vex::motor backLeftWheel = vex::motor(vex::PORT12, vex::ratio18_1, false);
vex::motor backRightWheel = vex::motor(vex::PORT19, vex::ratio18_1, true);

vex::motor intakeMotor = vex::motor(vex::PORT1, vex::gearSetting::ratio6_1, false);


vex::encoder leftEncoder = vex::encoder(Brain.ThreeWirePort.C); // Top wire is in port C, the bottom is in port D
vex::encoder rightEncoder = vex::encoder(Brain.ThreeWirePort.A);  // Top wire is in port B, the bottom is in port A
vex::encoder backEncoder = vex::encoder(Brain.ThreeWirePort.E);

vex::inertial inertialSensor = vex::inertial(vex::PORT1);
vex::gps gps = vex::gps(vex::PORT13, Mobius::Robot::gpsOffset.x, Mobius::Robot::gpsOffset.y, vex::distanceUnits::mm, 360 - Mobius::Robot::gpsOffset.angle, vex::turnType::right);

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
  // Calibrate the GPS
  if (gps.installed()) {
    Brain.Screen.print("Initialising GPS...");
    Brain.Screen.setCursor(3, 1);
    gps.calibrate();
    waitUntil(!gps.isCalibrating());
  }
  // Set the intake motor
  intakeMotor.setStopping(vex::brakeType::hold);

  // Initialise the field
  Brain.Screen.print("Initialising Field...");
  field.init();
  Brain.Screen.clearScreen();
}