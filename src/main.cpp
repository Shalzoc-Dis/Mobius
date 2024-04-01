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
extern Mobius::Field field;

// define your global instances of motors and other devices here


int main() {
    vexcodeInit();

    Mobius::Robot::driveSpeed = 1.0f;
    Mobius::Robot::controlState = Mobius::Robot::state::DRIVER_CONTROLLED;
    Mobius::Robot::currentMatchType = Mobius::Robot::matchType::ELIMINATION;

    while (true) {
        
        field.draw(5, 5, 230);

        //Mobius::Robot::MotionCalculators();

        /*
        // Spline testing
        Mobius::Spline spline;
        // Part 1
        spline.points.push_back(Mobius::vector2(0, 0));
        spline.points.push_back(Mobius::vector2(100, 0));
        spline.points.push_back(Mobius::vector2(100, 100));
        spline.points.push_back(Mobius::vector2(0, 100));
        // Part 2
        spline.points.push_back(Mobius::vector2(0, 100));
        spline.points.push_back(Mobius::vector2(-100, 100));
        spline.points.push_back(Mobius::vector2(-100, 200));
        spline.points.push_back(Mobius::vector2(0, 200));
        // This should look like an S shape
        */

        // Allow other tasks to run
        vex::this_thread::sleep_for(50);
    }
}
