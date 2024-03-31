#include "Robot.h"

namespace Mobius {
// Using this as reference: https://ecam-eurobot.github.io/Tutorials/mechanical/mecanum.html
// And https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf

void Robot::MotionCalculators() {

    float rotation = 0.0f; // In rads/s

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

            if (controllerPosition.magnitude() > 0.5f)
                Robot::desiredVelocity = controllerPosition / 100.0f; // The maximum value the controller can return for its magnitude is about 127.5
            else
                Robot::desiredVelocity = vector2(0.0f, 0.0f);

            if (controllerPosition.magnitude() > 100.0f) 
                Robot::desiredVelocity = controllerPosition.normalised();

            // Rotation
            if (std::abs((float)Controller1.Axis1.position()) > 1)
                rotation = -(float)Controller1.Axis1.position() / (15.0f * M_PI);   // Max value is 2.123 radians per second
            
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

    // Calculations


    // Variables for the motion
    float angularVel_FL = 0.0f;
    float angularVel_FR = 0.0f;
    float angularVel_BL = 0.0f;
    float angularVel_BR = 0.0f;

    vector2 v = Robot::desiredVelocity.rotate(-M_PI_2); // 0 in this formula is forwards, while 0 for the robot is right
    vector2 l = Robot::wheelOffset; l.x /= 100.0f; l.y /= 100.0f;   // Convert to metres
    float r = Robot::wheelRadius / 100.0f; // Convert to metres

    //Inverse Kinematics
    // ω is the angular velocity, v is the desired velocity, l is the distance from the center of the robot to the wheel 
    // ω = 1/r * (v_x - v_y - (l_x + l_y) * rotation)
    // Inputs of l are in metres, v is in m/s, rotation is in radians per second
    // Result is in radians per second

    angularVel_FL = 1/(r) * (v.x - v.y - (l.x + l.y) * rotation);
    angularVel_FR = 1/(r) * (v.x + v.y + (l.x + l.y) * rotation);
    angularVel_BL = 1/(r) * (v.x + v.y - (l.x + l.y) * rotation);
    angularVel_BR = 1/(r) * (v.x - v.y + (l.x + l.y) * rotation);

    // Maximum rpm of green motors is 200. 200 rpm is about 20.943951023931955 rad/sec
    // Normalise the speeds
    float largest = std::max(std::max(std::abs(angularVel_FL), std::abs(angularVel_FR)), std::max(std::abs(angularVel_BL), std::abs(angularVel_BR)));
    if (largest > 20.944f) {
        angularVel_FL /= largest;
        angularVel_FR /= largest;
        angularVel_BL /= largest;
        angularVel_BR /= largest;
    }
    // Make the angular velocity parametric
    angularVel_FL /= 20.944f;
    angularVel_FR /= 20.944f;
    angularVel_BL /= 20.944f;
    angularVel_BR /= 20.944f;

    // Adjust for drive speed and controller desired speed
    // If the robot is instructed to to a point turn, a velocity of 0 will keep it from moving. This is why this is here
    if (v.magnitude() > 0.1f) {
        angularVel_FL = angularVel_FL * Robot::driveSpeed * v.magnitude();
        angularVel_FR = angularVel_FR * Robot::driveSpeed * v.magnitude();
        angularVel_BL = angularVel_BL * Robot::driveSpeed * v.magnitude();
        angularVel_BR = angularVel_BR * Robot::driveSpeed * v.magnitude();
    }

    // Make sure one of the wheels is at the maximum speed set by the controller and drive speed. Unlock all the potential
    float parametricSpeedCap = Robot::driveSpeed * v.magnitude();
    largest = std::max(std::max(std::abs(angularVel_FL), std::abs(angularVel_FR)), std::max(std::abs(angularVel_BL), std::abs(angularVel_BR)));

    if (largest < parametricSpeedCap) {
        angularVel_FL = (angularVel_FL / largest) * parametricSpeedCap;
        angularVel_FR = (angularVel_FR / largest) * parametricSpeedCap;
        angularVel_BL = (angularVel_BL / largest) * parametricSpeedCap;
        angularVel_BR = (angularVel_BR / largest) * parametricSpeedCap;
    }

    // Drive the motors
    if (largest < 0.01f) {
        // Stop the robot
        frontRightWheel.stop(vex::brakeType::hold);
        frontLeftWheel.stop(vex::brakeType::hold);
        backRightWheel.stop(vex::brakeType::hold);
        backLeftWheel.stop(vex::brakeType::hold);
    } else {
        // Drive the motors
        frontRightWheel.spin(vex::directionType::fwd, angularVel_FR * 100, vex::velocityUnits::pct);
        frontLeftWheel.spin( vex::directionType::fwd, angularVel_FL * 100, vex::velocityUnits::pct);
        backRightWheel.spin( vex::directionType::fwd, angularVel_BR * 100, vex::velocityUnits::pct);
        backLeftWheel.spin(  vex::directionType::fwd, angularVel_BL * 100, vex::velocityUnits::pct);
    }
   

};  // void MotionCalculator()

} // namespace Mobius