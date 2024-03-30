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
                // desiredVelocity is parametric
                //TODO: The speed issues of the drivetrain have been traced to here. The desiredVelocity has the constant magnitude, which messes with the speed
                printf("Controller Position: %f, %f\n", controllerPosition.x, controllerPosition.y);
                Robot::desiredVelocity = controllerPosition / 100.0f; // The maximum value the controller can return for its magnitude is about 127.5
                printf("Desired Robot Speed: %f, %f\n", Robot::desiredVelocity.x, Robot::desiredVelocity.y);
                printf("Desired Robot Speed: %f\n\n", Robot::desiredVelocity.magnitude());
            } else {
                Robot::desiredVelocity = vector2(0.0f, 0.0f);
            }

            if (controllerPosition.magnitude() > 100.0f) {
                Robot::desiredVelocity = controllerPosition.normalised();
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
    if (std::abs((float)Controller1.Axis1.position()) > 1) {
        rotation = -(float)Controller1.Axis1.position() / (15.0f * M_PI);   // Max value is 2.123 radians per second
        printf("Rotation: %f\n", rotation);
    }
    
    
    // Variables for the motion

    float angularVel_FL = 0.0f;
    float angularVel_FR = 0.0f;
    float angularVel_BL = 0.0f;
    float angularVel_BR = 0.0f;

    vector2 l = Robot::wheelOffset; l.x /= 100.0f; l.y /= 100.0f;   // Convert to metres
    float r = Robot::wheelRadius / 100.0f; // Convert to metres

    vector2 v(0.0f, 0.0f);
    if (Robot::desiredVelocity.magnitude() > 0.1f /* || std::abs(rotation) > 0.0f */) {
        // While Driving

        if (Robot::desiredVelocity.magnitude() > 0.1f) {
            v = Robot::desiredVelocity.rotate(-M_PI_2); // 0 in this formula is forwards, while 0 for the robot is right
        }

        printf("Desired Robot Velocity: %f, %f\n", v.x, v.y);
        printf("Desired Robot Rotation: %f rpm\n", rotation *  9.549f);
        printf("Desired Robot Speed: %f\n\n", Robot::desiredVelocity.magnitude());

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
        angularVel_FL = angularVel_FL * Robot::driveSpeed * v.magnitude();
        angularVel_FR = angularVel_FR * Robot::driveSpeed * v.magnitude();
        angularVel_BL = angularVel_BL * Robot::driveSpeed * v.magnitude();
        angularVel_BR = angularVel_BR * Robot::driveSpeed * v.magnitude();

        printf("v: (%f, %f)\n", v.x, v.y);
        printf("v.magnitude() %f\n", v.magnitude());
        printf("angularVel_FL before: %f\n", angularVel_FL);
        printf("angularVel_FR before: %f\n", angularVel_FR);
        printf("angularVel_BL before: %f\n", angularVel_BL);
        printf("angularVel_BR before: %f\n\n", angularVel_BR);

        
        // Make sure one of the wheels is at the maximum speed set by the controller and drive speed. Unlock all the potential
        float parametricSpeedCap = Robot::driveSpeed * v.magnitude();
        largest = std::max(std::max(std::abs(angularVel_FL), std::abs(angularVel_FR)), std::max(std::abs(angularVel_BL), std::abs(angularVel_BR)));
        if (largest < parametricSpeedCap) {
            angularVel_FL = (angularVel_FL / largest) * parametricSpeedCap;
            angularVel_FR = (angularVel_FR / largest) * parametricSpeedCap;
            angularVel_BL = (angularVel_BL / largest) * parametricSpeedCap;
            angularVel_BR = (angularVel_BR / largest) * parametricSpeedCap;
        }

        printf("parametricSpeedCap: %f\n", parametricSpeedCap);
        printf("angularVel_FL after: %f\n", angularVel_FL);
        printf("angularVel_FR after: %f\n", angularVel_FR);
        printf("angularVel_BL after: %f\n", angularVel_BL);
        printf("angularVel_BR after: %f\n\n", angularVel_BR);
        
        // Drive the motors
        frontRightWheel.spin(vex::directionType::fwd, angularVel_FR * 100, vex::velocityUnits::pct);
        frontLeftWheel.spin( vex::directionType::fwd, angularVel_FL * 100, vex::velocityUnits::pct);
        backRightWheel.spin( vex::directionType::fwd, angularVel_BR * 100, vex::velocityUnits::pct);
        backLeftWheel.spin(  vex::directionType::fwd, angularVel_BL * 100, vex::velocityUnits::pct);

    } else if (Robot::desiredVelocity.magnitude() <= 0.1f && std::abs(rotation) > 0.0f) {
        // No translation, only rotation
        angularVel_FL = 1/(r) * -(l.x + l.y) * rotation;
        angularVel_FR = 1/(r) *  (l.x + l.y) * rotation;
        angularVel_BL = 1/(r) * -(l.x + l.y) * rotation;
        angularVel_BR = 1/(r) *  (l.x + l.y) * rotation;

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

        // Make sure one of the wheels is at the maximum speed 
        float parametricSpeedCap = rotation / 2.123f;
        largest = std::max(std::max(std::abs(angularVel_FL), std::abs(angularVel_FR)), std::max(std::abs(angularVel_BL), std::abs(angularVel_BR)));
        if (largest < parametricSpeedCap) {
            angularVel_FL = (angularVel_FL / largest) * parametricSpeedCap;
            angularVel_FR = (angularVel_FR / largest) * parametricSpeedCap;
            angularVel_BL = (angularVel_BL / largest) * parametricSpeedCap;
            angularVel_BR = (angularVel_BR / largest) * parametricSpeedCap;
        }

        printf("angularVel_FL Rotation: %f\n", angularVel_FL);
        printf("angularVel_FR Rotation: %f\n", angularVel_FR);
        printf("angularVel_BL Rotation: %f\n", angularVel_BL);
        printf("angularVel_BR Rotation: %f\n\n", angularVel_BR);



        // Drive the motors
        frontRightWheel.spin(vex::directionType::fwd, angularVel_FR * 100, vex::velocityUnits::pct);
        frontLeftWheel.spin( vex::directionType::fwd, angularVel_FL * 100, vex::velocityUnits::pct);
        backRightWheel.spin( vex::directionType::fwd, angularVel_BR * 100, vex::velocityUnits::pct);
        backLeftWheel.spin(  vex::directionType::fwd, angularVel_BL * 100, vex::velocityUnits::pct);

    } else {
        // Stop the robot
        frontRightWheel.stop(vex::brakeType::hold);
        frontLeftWheel.stop(vex::brakeType::hold);
        backRightWheel.stop(vex::brakeType::hold);
        backLeftWheel.stop(vex::brakeType::hold);
    }
    
    //printf("Desired Robot Speed: %f\n", Robot::desiredVelocity.magnitude());

    
    // If we integrate the wheels' angular velocities, we get a vector of its motion

};  // void MotionCalculator()

} // namespace Mobius