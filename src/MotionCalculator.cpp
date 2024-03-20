#include "Robot.h"

namespace Mobius {
// Using this as reference: https://ecam-eurobot.github.io/Tutorials/mechanical/mecanum.html
// And https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf

int MotionCalculator() {
    // Inputs:
    // - The desired position relative to the robot
    // - The speed
    // - isMoving
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

    // Desired velocity
    vector2 v = vector2(speed * cos(angle) * Robot::maxVelocityInDirection(angle), speed * sin(angle) * Robot::maxVelocityInDirection(angle));
    // Desired angular velocity
    //float ω_z = Robot::maxAngularVelocity(v) * rotation;
    

    //Inverse Kinematics
    // ω is the angular velocity, v is the desired velocity, l is the distance from the center of the robot to the wheel 
    // Result is in radians per second
    float ω_FL = 1/(Robot::wheelRadius) * (v.x - v.y - (Robot::wheelOffset.x + Robot::wheelOffset.y) * rotation);
    float ω_FR = 1/(Robot::wheelRadius) * (v.x + v.y + (Robot::wheelOffset.x + Robot::wheelOffset.y) * rotation);
    float ω_BL = 1/(Robot::wheelRadius) * (v.x + v.y - (Robot::wheelOffset.x + Robot::wheelOffset.y) * rotation);
    float ω_BR = 1/(Robot::wheelRadius) * (v.x - v.y + (Robot::wheelOffset.x + Robot::wheelOffset.y) * rotation);

    frontRightWheel.spin(vex::directionType::fwd, ω_FR / M_TWOPI * 60, vex::velocityUnits::rpm);
    frontLeftWheel.spin( vex::directionType::fwd, ω_FR / M_TWOPI * 60, vex::velocityUnits::rpm);
    backRightWheel.spin( vex::directionType::fwd, ω_FR / M_TWOPI * 60, vex::velocityUnits::rpm);
    backLeftWheel.spin(  vex::directionType::fwd, ω_FR / M_TWOPI * 60, vex::velocityUnits::rpm);


    vex::task::sleep(20);
};
return 0;
};  // int MotionCalculator()

} // namespace Mobius