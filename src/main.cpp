/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Hypatia                                                   */
/*    Created:      09/03/2024, 10:19:11                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "Robot.h"



// A global instance of vex::brain used for printing to the V5 brain screen
extern vex::brain       Brain;
extern Mobius::Field field;

// define your global instances of motors and other devices here


int main() {

    vex::task tControllerHUD(Mobius::Robot::ControllerHUD);
    vex::task tPositioningComputer(Mobius::Robot::PositioningComputer);

    // Run the pre-autonomous function.
    Mobius::Robot::init();

    if (Mobius::Robot::inCompetition) {
        // Set up callbacks for autonomous and driver control periods.
        printf("In Competition\n");
        Competition.autonomous(Mobius::Robot::autonomous);
        Competition.drivercontrol(Mobius::Robot::teleOp);
    } else {
        printf("Not in Competition\n");
        Mobius::Robot::teleOp();
    }

    

       

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


    // Prevent main from exiting with an infinite loop.
    while (true) {
        if (Competition.isAutonomous())
            Mobius::Robot::controlState = Mobius::Robot::state::AUTONOMOUS;
        else if (Competition.isDriverControl())
            Mobius::Robot::controlState = Mobius::Robot::state::DRIVER_CONTROLLED;
        else 
            Mobius::Robot::controlState = Mobius::Robot::state::DISABLED;

        vex::wait(100, vex::msec);
    }

}