/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       hypatia                                                   */
/*    Created:      09/03/2024, 10:19:11                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "Robot.h"



// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here


int main() {
    vexcodeInit();

    Mobius::Robot::driveSpeed = 1.0f;
    Mobius::Robot::controlState = Mobius::Robot::state::DRIVER_CONTROLLED;

    while (true) {

        Mobius::Robot::MotionCalculators();
        

        // Allow other tasks to run
        vex::this_thread::sleep_for(50);
    }
}
