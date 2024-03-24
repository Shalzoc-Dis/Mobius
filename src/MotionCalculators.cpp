#include "Robot.h"

namespace Mobius {
// Using this as reference: https://ecam-eurobot.github.io/Tutorials/mechanical/mecanum.html
// And https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf

void Robot::MotionCalculatorByVelocity() {
    // Inputs:
    // - The desired position relative to the robot
    // - The speed
    // - isMoving
    // Outputs:
    // - Commands to the wheels to move the robot to the desired position


    // Direction to drive in (0 is forwards, pi is backwards)
    //float angle = atan2(Robot::desiredPosition.y, Robot::desiredPosition.x);
    // Angle for testing
    float angle = Robot::driveAngle;

    bool shouldDrive = true;
    if (Robot::driveAngle == '0') {
        shouldDrive = false;
    } 
    // Desired heading
    //float rotation = Robot::desiredPosition.angle - Robot::FieldCentricPosition.angle;
    // Rotation for testing
    float rotation = 0;
    if (std::abs(Controller1.Axis1.position()) > 1) {
        rotation = Controller1.Axis1.position();
    }
    

    if (shouldDrive || rotation > 0.1f) {
        // Desired velocity (x direction is the front of the robot)
        vector2 v(0, 0);
        if (shouldDrive) {
            v = vector2(cos(angle), sin(angle)) * 100;  // The * 100 is to convert from m/s to cm/s
        }

        printf("Desired Robot Velocity: %f, %f\n", v.x, v.y);
        printf("Rotation: %ld\n\n", rotation);

        //Inverse Kinematics
        // ω is the angular velocity, v is the desired velocity, l is the distance from the center of the robot to the wheel 
        // Result is in radians per second
        float angularVel_FL = 1/(Robot::wheelRadius) * (v.x - v.y - (Robot::wheelOffset.x + Robot::wheelOffset.y) * rotation);
        float angularVel_FR = 1/(Robot::wheelRadius) * (v.x + v.y + (Robot::wheelOffset.x + Robot::wheelOffset.y) * rotation);
        float angularVel_BL = 1/(Robot::wheelRadius) * (v.x + v.y - (Robot::wheelOffset.x + Robot::wheelOffset.y) * rotation);
        float angularVel_BR = 1/(Robot::wheelRadius) * (v.x - v.y + (Robot::wheelOffset.x + Robot::wheelOffset.y) * rotation);

        // Normalise the speeds and factor in parametric speed
        float largest = std::max(std::max(std::abs(angularVel_FL), std::abs(angularVel_FR)), std::max(std::abs(angularVel_BL), std::abs(angularVel_BR)));
        angularVel_FL = angularVel_FL / largest * Robot::driveSpeed;
        angularVel_FR = angularVel_FR / largest * Robot::driveSpeed;
        angularVel_BL = angularVel_BL / largest * Robot::driveSpeed;
        angularVel_BR = angularVel_BR / largest * Robot::driveSpeed;

        printf("Front Left Wheel Angular Velocity: %f\n", angularVel_FL);
        printf("Front Right Wheel Angular Velocity: %f\n", angularVel_FR);
        printf("Back Left Wheel Angular Velocity: %f\n", angularVel_BL);
        printf("Back Right Wheel Angular Velocity: %f\n\n", angularVel_BR);

        // Convert radians per second to rpm and set motor velocity
        frontRightWheel.spin(vex::directionType::fwd, angularVel_FR * 60 / M_TWOPI, vex::velocityUnits::rpm);
        frontLeftWheel.spin( vex::directionType::fwd, angularVel_FL * 60 / M_TWOPI, vex::velocityUnits::rpm);
        backRightWheel.spin( vex::directionType::fwd, angularVel_BR * 60 / M_TWOPI, vex::velocityUnits::rpm);
        backLeftWheel.spin(  vex::directionType::fwd, angularVel_BL * 60 / M_TWOPI, vex::velocityUnits::rpm);
    }

    // If we integrate the wheels' angular velocities, we get a vector of its motion

};  // int MotionCalculator()

} // namespace Mobius