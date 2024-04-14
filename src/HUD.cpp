#include "Robot.h"



extern vex::competition Competition;
extern vex::brain Brain;
namespace Mobius {

int Robot::ControllerHUD() {
    // Driver Control HUD:          Autonomous HUD:
    //              11  15  19                  11  15  19
    //    1 3 5 7 9 ↓ 13↓ 17↓ 20       1 3 5 7 9 ↓ 13↓ 17↓ 20
    //   +--------------------+       +--------------------+
    // 1 |S000      FC    B000|     1 |S000      A     B000| 
    // 2 |                    |     2 |                    | 
    // 3 |T0:00               |     3 |T0:00               | 
    //   +--------------------+       +--------------------+ 
    // Columns: 1 though 19
    // Rows: 1 though 3

    vex::timer controlPeriodTimer;

while (true) {
    Controller1.Screen.clearScreen();

    // Speed
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("D%d", (int)(Robot::driveSpeed * 100.0f));

       


    // If under driver control
    if (!Competition.isEnabled()) {
        Controller1.Screen.setCursor(1, 7);
        Controller1.Screen.print("DISABLED");

    } else if (Robot::controlState == Robot::state::DRIVER_CONTROLLED) {

        // Field Centric or Robot Centric Control
        Controller1.Screen.setCursor(1, 11);
        if (Robot::currentControlMode == Robot::controlMode::FIELD_CENTRIC)
            Controller1.Screen.print("FC");
        else
            Controller1.Screen.print("RC");
        
    } else {
        // If under autonomous control
        Controller1.Screen.setCursor(1, 11);
        Controller1.Screen.print("A");


    }


    // Battery Percentage
    Controller1.Screen.setCursor(1, 17);
    Controller1.Screen.print("B%0.1d", (int)Brain.Battery.capacity());




    // Position
    /*
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print("X: %0.2f, Y: %0.2f", Robot::FieldCentricPosition.x, Robot::FieldCentricPosition.y);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("Head: %d", (int)(Robot::FieldCentricPosition.angle * 180 / M_PI));
    */

    // Debug
    /*
    Controller1.Screen.setCursor(1, 3);
    Controller1.Screen.print("|GPSH:%d|", (int)gps.heading());
    */

    
    vex::task::sleep(500);
} // while (true)
} // int ControllerHUD()
} // namespace Mobius
