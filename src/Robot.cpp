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
Position gpsOffset(-9.6f, -11.4f, 180); // In cm and degrees ccw

// State
state controlState;
controlMode currentControlMode;
matchType currentMatchType;
vector2 desiredVelocity;
float desiredAngularVelocity;

bool inCompetition;

fieldSide driverSide;
fieldSide GPS_0_Degree;

bool gpsAvailable;


void autonomous() {
    printf("Autonomous\n");
    // Implement autonomous here
    Mobius::Robot::controlState = Mobius::Robot::state::AUTONOMOUS;

    frontLeftWheel.spin(vex::directionType::rev);
    frontRightWheel.spin(vex::directionType::rev);
    backLeftWheel.spin(vex::directionType::rev);
    backRightWheel.spin(vex::directionType::rev);
    
    vex::wait(5, vex::timeUnits::sec);


    frontLeftWheel.spin(vex::directionType::fwd);
    frontRightWheel.spin(vex::directionType::fwd);
    backLeftWheel.spin(vex::directionType::fwd);
    backRightWheel.spin(vex::directionType::fwd);

    vex::wait(3, vex::timeUnits::sec);


    frontLeftWheel.stop();
    frontRightWheel.stop();
    backLeftWheel.stop();
    backRightWheel.stop();

    while (Robot::controlState == Robot::state::AUTONOMOUS) {
    

        Mobius::Robot::ManipulatorControl();
        Mobius::Robot::MotionCalculators();

        vex::task::sleep(20);

    }
}

void teleOp() {
    printf("TeleOp\n");
    // Implement usercontrol here
    Mobius::Robot::controlState = Mobius::Robot::state::DRIVER_CONTROLLED;

    while (Robot::controlState == Mobius::Robot::state::DRIVER_CONTROLLED) {
        //field.draw(5, 5, 230);
        Mobius::Robot::ManipulatorControl();
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

    if (gps.heading() == 360 || gps.quality() < 40) {
        Mobius::Robot::gpsAvailable = false;
        Mobius::Robot::currentControlMode = Mobius::Robot::controlMode::ROBOT_CENTRIC;
    } else {
        printf("GPS Locked\n");
        Mobius::Robot::gpsAvailable = true;
        Mobius::Robot::currentControlMode = Mobius::Robot::controlMode::FIELD_CENTRIC;
    }

    // Set the intake motor
    intakeMotor.setStopping(vex::brakeType::hold);

    // Initialise the field
    Brain.Screen.print("Initialising Field...");
    field.init();
    Brain.Screen.clearScreen();

    if (Competition.isCompetitionSwitch()) {
        Brain.Screen.print("Competition Switch");
        Robot::inCompetition = true;
    } else {
        Brain.Screen.print("No Competition Switch");
        Robot::inCompetition = false;
    }

    Mobius::Robot::driveSpeed = 1.0f;
    Mobius::Robot::currentMatchType = Mobius::Robot::matchType::HEAD_TO_HEAD;

    Mobius::Robot::driverSide = Mobius::Robot::fieldSide::BLUE_GOAL;
    // Middle field has the red bar at 0 degrees
    Mobius::Robot::GPS_0_Degree = Mobius::Robot::fieldSide::RED_BAR;

    ControllerCallbacks();
}

void ControllerCallbacks() {
    // Controller1
    // - Axis 1:    Robot rotation in driver control
    // - Axis 2:    Nothing
    // - Axis 3:    Front-Back drivetrain translation
    // - Axis 4:    Left-Right drivetrain translation
    // - Button A:  Toggle field centric and robot centric positioning
    // - Button B:  Switch Alliance
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
        }
        else {
            Mobius::Robot::currentControlMode = Mobius::Robot::controlMode::FIELD_CENTRIC;
        }
    });

    Controller1.ButtonL1.pressed([]() {
        Mobius::Robot::driveSpeed = 1.0f;
    });
    Controller1.ButtonL2.pressed([]() {
        Mobius::Robot::driveSpeed = 0.75f;
    });

    Controller1.ButtonB.pressed([]() {
        printf("B pressed");
        if (Mobius::Robot::driverSide == Mobius::Robot::fieldSide::BLUE_GOAL)
            Mobius::Robot::driverSide == Mobius::Robot::fieldSide::RED_GOAL;
        else
            Mobius::Robot::driverSide == Mobius::Robot::fieldSide::BLUE_GOAL;
    });



}

int checkGPS() {
    while (true) {

        if (gps.quality() < 40) {
            gpsAvailable = false;
            Controller1.rumble("---");
        } else 
            gpsAvailable = true;
            Controller1.rumble("..");

        vex::this_thread::sleep_for(10000);
    }
    return 0;
}

} // namespace Mobius::Robot   
} // namespace Mobius


