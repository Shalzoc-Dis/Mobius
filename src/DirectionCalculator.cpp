#include "Robot.h"


namespace Mobius { namespace Robot {

// This module takes in the current movement of the robot, what is controlling it, and what this thinks the robot should do

void DirectionCalculator() {

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
    if (std::abs(Controller1.Axis4.position()) > 1 || std::abs(Controller1.Axis3.position()) > 1) {
        Robot::desiredVelocity = vector2(Controller1.Axis4.position(), Controller1.Axis3.position());
        Robot::desiredVelocity = Robot::desiredVelocity / 127.0f;   // The maximum value the controller can return for this is 127
        Robot::driveAngle = atan2(Robot::desiredVelocity.y, Robot::desiredVelocity.x);
    } else {
        Robot::driveAngle = '0';    // This means the robot should not move
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
} // DirectionCalculator()

} // namespace Mobius::Robot
} // namespace Mobius