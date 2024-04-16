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


void testing();

int main() {

    vex::task tControllerHUD(Mobius::Robot::ControllerHUD);
    vex::task tPositioningComputer(Mobius::Robot::PositioningComputer);

    // Run the pre-autonomous function.
    Mobius::Robot::init();

    // Testing only
    tPositioningComputer.stop();
    Mobius::Robot::FieldCentricPosition.x = 50;
    Mobius::Robot::FieldCentricPosition.y = 50;
    testing();


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


void testing () {
    printf("Creating Path...\n");
    Mobius::Robot::Path path;
    // Part 1
    path.m_points.push_back(Mobius::Position(20, 20, 0));
    path.m_points.push_back(Mobius::Position(100, 20, 0));
    path.m_points.push_back(Mobius::Position(150, 100, 0));
    path.m_points.push_back(Mobius::Position(60, 200, 0));

    // Create action
    printf("Creating Action...\n");
    Mobius::Robot::Action fc1(path.getNthCurve(0), 0.05, 1);
    // Create plan
    printf("Creating Plan...\n");
    Mobius::Robot::AutonomousPlan testingPlan1;
    testingPlan1.m_actions.push_back(fc1);

    printf("Executing Plan...\n");
    testingPlan1.execute();

    // This should look like an S shape

}