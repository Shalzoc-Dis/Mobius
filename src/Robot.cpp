#include "Robot.h"


vex::competition Competition;
vex::brain Brain;

namespace Mobius { namespace Robot {

Mobius::Field field;


// Implementations of the vaiables in Robot.h
Position FieldCentricPosition(0, 0, 0);
Position desiredPosition(0, 0, 0);
float driveAngle;
float driveSpeed;
// Velocity and Acceleration
vector2 velocity;    // In cm/s
float angularVelocity; // In radians/s
vector2 acceleration; // In cm/s^2
float angularAcceleration; // In radians/s^2
vector2 momentum;

// Physical Characteristics
float width = 42.4, length = 20.5, height = 10; // In cm
Position gpsOffset(-width / 2, 0, 90); // In cm and degrees ccw

// State
state controlState;
controlMode currentControlMode;
matchType currentMatchType;
vector2 desiredVelocity;
float desiredAngularVelocity;

fieldSide driverSide;
fieldSide GPS_0_Degree;

bool gpsAvailable;


void autonomous() {
    printf("Autonomous\n");
    // Implement autonomous here
    Mobius::Robot::controlState = Mobius::Robot::state::AUTONOMOUS;
}

void teleOp() {
    printf("TeleOp\n");
    // Implement usercontrol here
    Mobius::Robot::controlState = Mobius::Robot::state::DRIVER_CONTROLLED;

    while (true) {
        //field.draw(5, 5, 230);
        Mobius::Robot::ManipulatorControl();
        //Mobius::Robot::PositioningComputer();
        Mobius::Robot::MotionCalculators();

        vex::task::sleep(20);
    }
}

void init() {
    // Implement pre_auton here
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


    Mobius::Robot::driveSpeed = 1.0f;
    Mobius::Robot::currentControlMode = Mobius::Robot::controlMode::FIELD_CENTRIC;
    Mobius::Robot::currentMatchType = Mobius::Robot::matchType::HEAD_TO_HEAD;

    Mobius::Robot::driverSide = Mobius::Robot::fieldSide::RED_BAR;
    Mobius::Robot::GPS_0_Degree = Mobius::Robot::fieldSide::BLUE_BAR;
    Mobius::Robot::gpsAvailable = true;

    ControllerCallbacks();
}

void ControllerCallbacks() {
    // Controller1
    // - Axis 1:    Robot rotation in driver control
    // - Axis 2:    Nothing
    // - Axis 3:    Front-Back drivetrain translation
    // - Axis 4:    Left-Right drivetrain translation
    // - Button A:  Toggle field centric and robot centric positioning
    // - Button B:  Nothing
    // - Button X:  //TODO Dash mode (robot turns to face the movement direction in driver control and field centric mode)
    // - Button Y:  Nothing
    // - R1:        //Intake in
    // - R2:        //Intake out
    // - L1:        //TODO Robot speed high
    // - L2:        //TODO Robot speed low


    // A toggles field centric and robot centric positioning
    Controller1.ButtonA.released([]() {
        if (Mobius::Robot::currentControlMode == Mobius::Robot::controlMode::FIELD_CENTRIC) {
            Mobius::Robot::currentControlMode = Mobius::Robot::controlMode::ROBOT_CENTRIC;
            printf("Robot centric\n");
        }
        else {
            Mobius::Robot::currentControlMode = Mobius::Robot::controlMode::FIELD_CENTRIC;
            printf("Field centric\n");
        }
    });

    Controller1.ButtonL1.pressed([]() {
        Mobius::Robot::driveSpeed = 1.0f;
    });
    Controller1.ButtonL2.pressed([]() {
        Mobius::Robot::driveSpeed = 0.75f;
    });

}



} // namespace Mobius::Robot   
} // namespace Mobius


