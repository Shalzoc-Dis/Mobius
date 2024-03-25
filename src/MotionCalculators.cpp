#include "Robot.h"

namespace Mobius {
// Using this as reference: https://ecam-eurobot.github.io/Tutorials/mechanical/mecanum.html
// And https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf

void Robot::MotionCalculators() {
    switch (Robot::controlState) {
        case Robot::state::AUTONOMOUS:
        break;
        case Robot::state::DRIVER_CONTROLLED:
            // TODO: Take joystick input and get desired direction from that.
            // Take in the direction the joysticks are pointing
            // Take in the current position of the robot
            // Take in the current motion of the robot
            // Calculate the direction the robot must drive in to reach the desired position

            // Basic movement
            // The robot should move in the direction of the joystick
            vector2 controllerPosition((float)Controller1.Axis4.position(), (float)Controller1.Axis3.position());
            if (controllerPosition.magnitude() > 1) {
                Robot::desiredVelocity = controllerPosition / 127.0f; // The maximum value the controller can return for this is 127
            } else {
                Robot::desiredVelocity = vector2(0.0f, 0.0f);
            }
            // It needs to correct for the robot not being on a path (autonomous)
            // It needs to adjust the heading as well. The heading influences the maximum speed of the robot, so this is important
            // It needs to correct for centripetal force

            // Calculate where the robot is going to be if it continues in a straight line at constant speed
            Robot::momentum = Robot::velocity / 100 * Robot::mass;

            // Calculate where the robot will stop if told to stop moving


            // The second derivative of the bezier curve gives us the direction it wants us to go
            // The magnitude of this can be ignored because it the robot's desired speed is defined elsewhere




        break;
    }
    // Inputs:
    // - The desired position relative to the robot
    // - The speed
    // - isMoving
    // Outputs:
    // - Commands to the wheels to move the robot to the desired position


    // Rotation for testing
    float rotation = 0.0f; // In rads/s
    if (std::abs((float)Controller1.Axis2.position()) > 1) {
        rotation = -(float)Controller1.Axis2.position() / (200 * M_PI);
    }
    
    
    vector2 v(0.0f, 0.0f);
    if (Robot::desiredVelocity.magnitude() > 0.1f || std::abs(rotation) > 0.0f) {

        if (Robot::desiredVelocity.magnitude() > 0.1f) {
            v = Robot::desiredVelocity.rotate(-M_PI_2); // 0 in this formula is forwards, while 0 for the robot is right
        }

        
        printf("Desired Robot Velocity: %f, %f\n", v.x, v.y);
        printf("Desired Robot Rotation: %f\n", rotation);
        printf("Desired Robot Speed: %f\n\n", Robot::desiredVelocity.magnitude());

        //Inverse Kinematics
        // ω is the angular velocity, v is the desired velocity, l is the distance from the center of the robot to the wheel 
        // Result is in radians per second
        float angularVel_FL = 1/(Robot::wheelRadius) * (v.x - v.y - (Robot::wheelOffset.x + Robot::wheelOffset.y) * rotation);
        float angularVel_FR = 1/(Robot::wheelRadius) * (v.x + v.y + (Robot::wheelOffset.x + Robot::wheelOffset.y) * rotation);
        float angularVel_BL = 1/(Robot::wheelRadius) * (v.x + v.y - (Robot::wheelOffset.x + Robot::wheelOffset.y) * rotation);
        float angularVel_BR = 1/(Robot::wheelRadius) * (v.x - v.y + (Robot::wheelOffset.x + Robot::wheelOffset.y) * rotation);

        // Normalise the speeds and factor in parametric speed
        float largest = std::max(std::max(std::abs(angularVel_FL), std::abs(angularVel_FR)), std::max(std::abs(angularVel_BL), std::abs(angularVel_BR)));
        if (largest > 1.0f) {
            angularVel_FL /= largest;
            angularVel_FR /= largest;
            angularVel_BL /= largest;
            angularVel_BR /= largest;
        }
       
        printf("Front Left Wheel Angular Velocity: %f\n", angularVel_FL);
        printf("Front Right Wheel Angular Velocity %f\n", angularVel_FR);
        printf("Back Left Wheel Angular Velocity:  %f\n", angularVel_BL);
        printf("Back Right Wheel Angular Velocity: %f\n\n", angularVel_BR);

        // Convert radians per second to rpm and set motor velocity
        frontRightWheel.spin(vex::directionType::fwd, angularVel_FR * Robot::driveSpeed * 100.0f, vex::velocityUnits::pct);
        frontLeftWheel.spin( vex::directionType::fwd, angularVel_FL * Robot::driveSpeed * 100.0f, vex::velocityUnits::pct);
        backRightWheel.spin( vex::directionType::fwd, angularVel_BR * Robot::driveSpeed * 100.0f, vex::velocityUnits::pct);
        backLeftWheel.spin(  vex::directionType::fwd, angularVel_BL * Robot::driveSpeed * 100.0f, vex::velocityUnits::pct);
    } else {
        // Stop the robot
        frontRightWheel.stop(vex::brakeType::hold);
        frontLeftWheel.stop(vex::brakeType::hold);
        backRightWheel.stop(vex::brakeType::hold);
        backLeftWheel.stop(vex::brakeType::hold);
    }
    
    //printf("Desired Robot Speed: %f\n", Robot::desiredVelocity.magnitude());


    // If we integrate the wheels' angular velocities, we get a vector of its motion

};  // int MotionCalculator()

} // namespace Mobius