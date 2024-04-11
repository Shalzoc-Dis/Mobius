#include "Robot.h"


Mobius::Field field;

float Mobius::Robot::maxVelocityInDirection(float angle) {
    //                               2πr * rev/min * 60min/s * mysteryConstant
    const float maxForwardVelocity = Robot::wheelRadius * M_TWOPI * 200 * 60 * 1.0f;
    const float maxSidewaysVelocity = 1;
    return 1.0f;
};

float Mobius::Robot::maxAngularVelocity(vector2 velocity) {
    return 1.0f;
};


namespace Mobius { namespace Robot {
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


int ControllerHUD() {
while (true) {
    Controller1.Screen.clearScreen();
    // Field Centric or Robot Centric Control
    Controller1.Screen.setCursor(1, 1);
    if (Robot::currentControlMode == Robot::controlMode::FIELD_CENTRIC)
        Controller1.Screen.print("FC");
    else
        Controller1.Screen.print("RC");

    // Position
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print("X: %0.2f, Y: %0.2f", Robot::FieldCentricPosition.x, Robot::FieldCentricPosition.y);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("Head: %d", (int)(Robot::FieldCentricPosition.angle * 180 / M_PI));

    // Debug
    Controller1.Screen.setCursor(1, 4);
    Controller1.Screen.print("GPSH: %d", (int)gps.heading());


    vex::task::sleep(750);
}   
}

} // namespace Mobius::Robot   
} // namespace Mobius