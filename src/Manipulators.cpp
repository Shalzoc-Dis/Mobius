#include "Robot.h"

namespace Mobius { namespace Robot {

void Robot::ManipulatorControl() {
    

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