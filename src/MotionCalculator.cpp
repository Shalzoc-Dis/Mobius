#include "Robot.h"

namespace Mobius {
// Using this as reference: https://seamonsters-2605.github.io/archive/mecanum/#:~:text=Analyzing%20Mecanum%20Wheels&text=The%20easiest%20way%20to%20figure,and%20no%20power%20is%200.&text=The%20table%20above%20shows%20the,wheel%20at%20the%20given%20angles.
int MotionCalculator() {
    // Inputs:
    // - The desired position relative to the robot
    // - The speed
    // Outputs:
    // - Commands to the wheels to move the robot to the desired position
while (true) {

    // Direction to drive in
    float angle = atan2(Robot::desiredPosition.y, Robot::desiredPosition.x);
    // Desired heading
    float rotation = Robot::desiredPosition.angle - Robot::FieldCentricPosition.angle;
    // Distance to position
    float distance = sqrt(pow(Robot::desiredPosition.x, 2) + pow(Robot::desiredPosition.y, 2));
    // Desired parametric speed
    float speed = Robot::driveSpeed;
    
    // Table of wheel powers vs. drive direction
    //      π/4 radians | 3π/4 radians | 5π/4 radians  | 7π/4 radians
    // FL |     1       |      0       |      -1       |      0
    // FR |     0       |      1       |       0       |     -1
    // BL |     0       |      1       |       0       |     -1
    // BR |     1       |      0       |      -1       |      0

    // The FR and BL motors are controlled by power = sin(angle - π/4)
    // The FL and BR motors are controlled by power = sin(angle + π/4)

    // Calculate turning
    float turn = 0;

    float FL_Power = speed * sin(angle + M_PI/4) * 100 + turn;
    float FR_Power = speed * sin(angle - M_PI/4) * 100 - turn;
    float BL_Power = speed * sin(angle - M_PI/4) * 100 + turn;
    float BR_Power = speed * sin(angle + M_PI/4) * 100 - turn;

    // Normalising the powers
    float max = FL_Power;
    if (FR_Power > max) max = FR_Power;
    if (BL_Power > max) max = BL_Power;
    if (BR_Power > max) max = BR_Power;

    FL_Power /= max;
    FR_Power /= max;
    BL_Power /= max;
    BR_Power /= max;


    // Motor commands
    if (speed > 0) {
        frontLeftWheel.spin(vex::directionType::fwd, FL_Power, vex::velocityUnits::pct);
        frontRightWheel.spin(vex::directionType::fwd, speed * sin(angle - M_PI/4) * 100, vex::velocityUnits::pct);
        backLeftWheel.spin(vex::directionType::fwd, speed * sin(angle - M_PI/4) * 100, vex::velocityUnits::pct);
        backRightWheel.spin(vex::directionType::fwd, speed * sin(angle + M_PI/4) * 100, vex::velocityUnits::pct);
    }

    vex::task::sleep(20);
};
return 0;
};

} // namespace Mobius