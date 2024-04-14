#include "Robot.h"

namespace Mobius { namespace Robot {

void Robot::ManipulatorControl() {
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


    // Intake
    if (Controller1.ButtonR1.pressing()) {
        // Intake in
        intakeMotor.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    } else if (Controller1.ButtonR2.pressing()) {
        // Intake out
        intakeMotor.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    } else {
        // Stop the intake
        intakeMotor.stop(vex::brakeType::hold);
    }
}

} // namespace Robot
} // namespace Mobius